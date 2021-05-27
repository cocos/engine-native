'use strict';

const chalk = require('chalk');
const path = require("path");
const { existsSync, removeSync } = require('fs-extra');

// npm run clear-platform
// 清理仓库内的与平台无关的第三方库
let externalDir = path.join(__dirname, "../external");
let failed = false;
main();

function main() {
    clearUselessPlatform();
}

function clearUselessPlatform() {
    console.log(chalk.magenta(`==== 移除平台无关第三方库 ====`));
    console.log(`  ${chalk.green('当前平台: ')} ${process.platform}`);
    console.log(`  ${chalk.green('第三方库目录: ')} ${externalDir}`);
    if (process.platform === 'darwin') {
        // remove win32 related 3rd-libs
        console.log(chalk.magenta(`==== 移除win32第三方库 ====`));
        let clearDirectory = path.join(externalDir, "./win32");
        console.log(`  ${chalk.green('清理目录: ')} ${clearDirectory}`);
        ensureRemove(clearDirectory);
    } else {
        // remove apple related 3rd-libs
        console.log(chalk.magenta(`==== 移除apple第三方库 ====`));
        let clearDirectory = path.join(externalDir, "./mac");
        console.log(`  ${chalk.green('清理目录: ')} ${clearDirectory}`);
        ensureRemove(clearDirectory);
        clearDirectory = path.join(externalDir, "./ios");
        console.log(`  ${chalk.green('清理目录: ')} ${clearDirectory}`);
        ensureRemove(clearDirectory);
    }
    // 异常退出
    if (failed) {
        process.exit(-1);
    }
}

function ensureRemove(clearDirectory) {
    try {
        if (existsSync(clearDirectory)) {
            removeSync(clearDirectory);
            console.log(`  ${chalk.green('成功')}`);
        } else {
            console.log(`  ${chalk.yellow('目录不存在: 跳过')}`);
        }
    } catch (error) {
        failed = true;
        console.log(`  ${chalk.red('失败')}`);
        console.log(error);
    }
}


