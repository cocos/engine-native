@echo off 
:begin
echo start build

chcp 65001

set buildMode=bc

set enginePath=E:\CocosDashboard_1.2.5\resources\.editors\Creator\2.4.11\CocosCreator.exe

set gamePath=E:\cocos\2.4.11Test

set tempPath=jsb-link

echo %buildMode% | findstr a >nul && (
     %enginePath% --path %gamePath% --build "platform=android"

    echo start clean
    IF EXIST %tempPath% ( rd /s /q  %tempPath% )

    echo start copy
    xcopy /y %gamePath%\build\%tempPath%\*.* %tempPath%\ /s /e  
) || (
   echo no neeed to build Android jsb-link
)

echo %buildMode% | findstr b >nul && (
    IF EXIST %tempPath% (
        IF EXIST node_modules (
             echo already install gulp 
        ) ELSE ( 
            echo install gulp
            call npm install 
        ) 
        call cmd /c gulp default --path %tempPath%
    )ELSE (
        echo pls check jsb_link or jsb_default
        pause
    )
) || (
   echo no need to build openHarmony
)

set /a ver=0
for /f "tokens=3" %%g in ('java -version 2^>^&1 ^| findstr /i "version"') do (
    set JAVAVER=%%g
)
set JAVAVER=%JAVAVER:"=%
for /f "delims=. tokens=1-3" %%v in ("%JAVAVER%") do (
    set ver=%%v
)
set /a v=11

echo %buildMode% | findstr c >nul && (
    echo install lib
    cd .\openharmony\entry\lib
    IF EXIST cocos-lib-1.0.0.tgz ( del .\cocos-lib-1.0.0.tgz /s)
    npm pack
    cd..
    IF EXIST oh_modules ( rd /s /q  oh_modules )
    ohpm install
    cd..
    echo build hap begin
    hvigorw clean assembleHap --no-daemon debuggable=false
   
    IF %ver% GTR %v% (
        cd..
        copy /y .\openharmony\entry\build\default\outputs\default\entry-default-unsigned.hap sign_tools\
        cd sign_tools
        java -jar hap-sign-tool.jar sign-profile -mode "localSign" -keyAlias "OpenHarmony Application Profile Release" -keyPwd "123456" -inFile "UnsgnedReleasedProfileTemplate.json" -outFile "myApplication_ohos_Provision.p7b" -keystoreFile "OpenHarmony.p12" -keystorePwd "123456"  -signAlg "SHA256withECDSA" -profileCertFile "OpenHarmonyProfileRelease.pem"
        java -jar hapsigntoolv2.jar sign -mode localjks -privatekey "OpenHarmony Application Release" -inputFile entry-default-unsigned.hap -outputFile entry-release-signed.hap -keystore "OpenHarmony.p12" -keystorepasswd 123456 -keyaliaspasswd 123456 -signAlg SHA256withECDSA -profile "myApplication_ohos_Provision.p7b" -certpath "OpenHarmonyApplication.pem"
        echo build success hap in .\sign_tools\entry-release-signed.hap
    )ELSE (
        echo Failed to sign. Upgrade the Java version to a version later than 11.
    )
    pause
) || (
   echo not build hap
)

:end
