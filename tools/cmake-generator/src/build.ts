
import ps from 'path';
import fs from 'fs-extra';
import cp from 'child_process';

const staticRoot = ps.join(__dirname, '..', 'static');

export async function generate(options: generate.Options) {
    console.debug(`Generate options: ${JSON.stringify(options, undefined, 2)}`);
    await fs.ensureDir(options.out);
    const cMakeArgs: string[] = [
        `--log-level=VERBOSE`,
        `-GVisual Studio 16 2019`,
        `-AWin32`,
        `-DCREATOR_PROJECT_NAME=${options.name}`,
        `-DCOCOS_SDK_ROOT:PATH=${options.sdk}`,
        '-S',
        `${ps.join(staticRoot, 'project')}`,
        '-B',
        `${options.out}`,
    ];
    const cMakeProcess = cp.spawn('cmake', cMakeArgs, { });
    console.debug(`cmake ${cMakeArgs.join(' ')}`);
    cMakeProcess.stdout.on('data', (data) => {
        console.log(data.toString());
    });
    cMakeProcess.stderr.on('data', (data) => {
        console.error(data.toString());
    });
}

export namespace generate {
    export interface Options {
        name: string;
        path: string;
        out: string;
        platform: Platform;
        sdk: string;
    }

    export enum Platform {
        win32,
    
    }
}

async function safelyCopyFilesInto(source: string, dest: string, files: string[]) {
    for (const file of files) {
       const oFile =  ps.join(dest, file);
       await fs.ensureDir(oFile);
       await fs.copyFile(ps.join(source, file), oFile);
    }
}