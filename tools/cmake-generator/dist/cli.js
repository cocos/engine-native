"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __generator = (this && this.__generator) || function (thisArg, body) {
    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;
    return g = { next: verb(0), "throw": verb(1), "return": verb(2) }, typeof Symbol === "function" && (g[Symbol.iterator] = function() { return this; }), g;
    function verb(n) { return function (v) { return step([n, v]); }; }
    function step(op) {
        if (f) throw new TypeError("Generator is already executing.");
        while (_) try {
            if (f = 1, y && (t = op[0] & 2 ? y["return"] : op[0] ? y["throw"] || ((t = y["return"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;
            if (y = 0, t) op = [op[0] & 2, t.value];
            switch (op[0]) {
                case 0: case 1: t = op; break;
                case 4: _.label++; return { value: op[1], done: false };
                case 5: _.label++; y = op[1]; op = [0]; continue;
                case 7: op = _.ops.pop(); _.trys.pop(); continue;
                default:
                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }
                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }
                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }
                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }
                    if (t[2]) _.ops.pop();
                    _.trys.pop(); continue;
            }
            op = body.call(thisArg, _);
        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }
        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };
    }
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
var yargs_1 = __importDefault(require("yargs"));
var build_1 = require("./build");
var path_1 = __importDefault(require("path"));
function main() {
    var _a;
    return __awaiter(this, void 0, void 0, function () {
        var generateOptions;
        return __generator(this, function (_b) {
            switch (_b.label) {
                case 0:
                    yargs_1.default.help();
                    yargs_1.default.option('name', {
                        type: 'string',
                        demandOption: true,
                        description: 'Project name.',
                    });
                    yargs_1.default.option('path', {
                        type: 'string',
                        demandOption: true,
                        description: 'Project path.',
                    });
                    yargs_1.default.option('out', {
                        type: 'string',
                        demandOption: true,
                        description: 'Output directory.',
                    });
                    yargs_1.default.option('platform', {
                        description: 'Target platform',
                    });
                    yargs_1.default.option('sdk', {
                        type: 'string',
                        description: 'Cocos native SDK.'
                    });
                    generateOptions = {
                        name: yargs_1.default.argv.name,
                        path: yargs_1.default.argv.path,
                        out: yargs_1.default.argv.out,
                        platform: build_1.generate.Platform.win32,
                        sdk: (_a = yargs_1.default.argv.sdk, (_a !== null && _a !== void 0 ? _a : path_1.default.join(__dirname, '..', '..', '..'))),
                    };
                    return [4 /*yield*/, build_1.generate(generateOptions)];
                case 1:
                    _b.sent();
                    return [2 /*return*/];
            }
        });
    });
}
(function () { return __awaiter(void 0, void 0, void 0, function () {
    return __generator(this, function (_a) {
        switch (_a.label) {
            case 0: return [4 /*yield*/, main()];
            case 1:
                _a.sent();
                return [2 /*return*/];
        }
    });
}); })();
//# sourceMappingURL=cli.js.map