
import yargs from 'yargs';
import { generate } from './build';
import ps from 'path';

async function main() {
    yargs.help();
    yargs.option('name', {
        type: 'string',
        demandOption: true,
        description: 'Project name.',
    });
    yargs.option('path', {
        type: 'string',
        demandOption: true,
        description: 'Project path.',
    });
    yargs.option('out', {
        type: 'string',
        demandOption: true,
        description: 'Output directory.',
    });
    yargs.option('platform', {
        description: 'Target platform',
    });
    yargs.option('sdk', {
        type: 'string',
        description: 'Cocos native SDK.'
    });

    const generateOptions: generate.Options = {
        name: yargs.argv.name as string,
        path: yargs.argv.path as string,
        out: yargs.argv.out as string,
        platform: generate.Platform.win32,
        sdk: (yargs.argv.sdk as string | undefined) ?? ps.join(__dirname, '..', '..', '..'),
    };

    await generate(generateOptions);
}

(async () => {
    await main();
})();