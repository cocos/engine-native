// Script for compiling build behavior. It is built in the build plug-in and cannot be modified currently.
import { getHvigorNode } from '@ohos/hvigor'
import { hapTasks } from '@ohos/hvigor-ohos-plugin'
import * as path from 'path'
// import { executeOnlineSign } from '../hw_sign/sign.js'

const mModule = getHvigorNode(__filename)
const ohosPlugin = hapTasks(mModule)

const onlineSignHapTaskName = "onlineSignHap"
const curTargetName = "default"
const mModuleName = mModule.getName()
const projectRootPath = process.cwd()

const entryName = '';

const onlineSignTask = mModule.task(() => {
  const moduleBuildOutputDir = path.resolve(projectRootPath, mModuleName, 'build/default/outputs/default/')

  const inputFile = path.resolve(moduleBuildOutputDir, `${mModuleName}${entryName? '-' + entryName: ''}-default-unsigned.hap`)
  const outputFile = path.resolve(moduleBuildOutputDir, `${mModuleName}${entryName? '-' + entryName: ''}-default-signed.hap`)

  // executeOnlineSign(inputFile, outputFile)
}, onlineSignHapTaskName).dependsOn(`${curTargetName}@PackageHap`)

mModule.getTaskByName("assembleHap").dependsOn(onlineSignHapTaskName)

module.exports = {
  ohos: ohosPlugin
}
