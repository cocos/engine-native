const path = require("path");
const child_process = require('child_process');

const projectRootPath = process.cwd()
const userName = process.env.W3_ACCOUNT;
const password = process.env.W3_PASSWORD;
const onlineSignServer = 'http://cpki-kms.cbg.huawei.com:18888/sign';
const hapSignTool = 'hap-sign-tool.jar';
const hapSignOnlinePlugin = 'hapsign-online-plugin.jar';
const p7bFileName = 'debug.p7b';
const keyAlias = 'HOS Application Provision Debug';

const signMaterialPath = path.resolve(projectRootPath, 'hw_sign');

// 调用签名工具执行签名的具体逻辑,需要根据各自需求和场景自行实现
// Tips: 在IDE场景下,在线签名工具生成的签名后的hap必须默认仍然放置到/build/default/outputs/default/目录下,且包名以signed.hap为后缀
function executeOnlineSign(inputFile, outputFile) {
    const signToolFile = path.resolve(signMaterialPath, hapSignTool);
    const p7bFile = path.resolve(signMaterialPath, p7bFileName);

    const command = [
        "-jar",
        signToolFile,
        "sign-app",
        "-mode",
        "remoteSign",
        "-signServer",
        onlineSignServer,
        "-signerPlugin",
        hapSignOnlinePlugin,
        "-onlineAuthMode",
        "account",
        "-username",
        userName,
        "-userPwd",
        password,
        "-profileFile",
        p7bFile,
        "-compatibleVersion",
        "8",
        "-signAlg",
        "SHA256withECDSA",
        "-keyAlias",
        keyAlias,
        "-inFile",
        inputFile,
        "-outFile",
        outputFile
    ]

    const result = child_process.spawnSync("java", command, {
        encoding: 'utf-8',
        windowsHide: true
    });
    if (result.stderr) {
        console.error(result.stderr.trim());
    }
}

module.exports = {
    executeOnlineSign: executeOnlineSign
}