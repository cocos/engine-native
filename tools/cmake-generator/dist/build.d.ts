export declare function generate(options: generate.Options): Promise<void>;
export declare namespace generate {
    interface Options {
        name: string;
        path: string;
        out: string;
        platform: Platform;
        sdk: string;
    }
    enum Platform {
        win32 = 0
    }
}
