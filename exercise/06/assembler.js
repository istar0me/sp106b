var fs = require('fs') // 引入 fs 模組，用來讀取與寫入檔案
var asmPath = process.argv[2] // 要輸入的彙編檔

// Compare Table
var cTable = {
    "0": 0b0101010,
    "1": 0b0111111,
    "-1": 0b0111010,
    "D": 0b0001100,
    "A": 0b0110000,
    "M": 0b1110000,
    "!D": 0b0001101,
    "!A": 0b0110001,
    "!M": 0b1110001,
    "-D": 0b0001111,
    "-A": 0b0110011,
    "-M": 0b1110011,
    "D+1": 0b0011111,
    "A+1": 0b0110111,
    "M+1": 0b1110111,
    "D-1": 0b0001110,
    "A-1": 0b0110010,
    "M-1": 0b1110010,
    "D+A": 0b0000010,
    "D+M": 0b1000010,
    "D-A": 0b0010011,
    "D-M": 0b1010011,
    "A-D": 0b0000111,
    "M-D": 0b1000111,
    "D&A": 0b0000000,
    "D&M": 0b1000000,
    "D|A": 0b0010101,
    "D|M": 0b1010101
}

// Destination Table
var dTable = {
    "": 0b000,
    "M": 0b001,
    "D": 0b010,
    "MD": 0b011,
    "A": 0b100,
    "AM": 0b101,
    "AD": 0b110,
    "AMD": 0b111
}

// Jump Table
var jTable = {
    "": 000,
    "JGT": 0b001,
    "JEQ": 0b010,
    "JGE": 0b011,
    "JLT": 0b100,
    "JNE": 0b101,
    "JLE": 0b110,
    "JMP": 0b111
}

// Symbol Table (with Predefined label)
var symbolTable = {
    "R0": 0,
    "SP": 0,
    "R1": 1,
    "LCL": 1,
    "R2": 2,
    "ARG": 2,
    "R3": 3,
    "THIS": 3,
    "R4": 4,
    "THAT": 4,
    "R5": 5,
    "R6": 6,
    "R7": 7,
    "R8": 8,
    "R9": 9,
    "R10": 10,
    "R11": 11,
    "R12": 12,
    "R13": 13,
    "R14": 14,
    "R15": 15,
    "SCREEN": 16384,
    "KBD": 24576
}

var symTop = 16 // 使用者自定義符號的開頭位址
function addSymbol(symbol) {
    symbolTable[symbol] = symTop;
    symTop++;
}

// 組譯
function assemble(asmPath, hackPath) {
    console.log(`【彙編檔 : ${asmPath} 】`)
    var asmFile = fs.readFileSync(asmPath, "utf-8") // 以 UTF-8 的格式讀入檔案
    var splitedAsm = asmFile.split(/\r?\n/) // 拆成一行一行的陣列
    // printAlignedDash(splitedAsm[0].length)
    // printLineNum(splitedAsm, 10, 3)
    var jsonAsm = JSON.stringify(splitedAsm, null, 2) // 轉換為 JSON 格式
    console.log(jsonAsm)
    checkType(splitedAsm)
    convert(splitedAsm, hackPath)
}
assemble(`${asmPath}.asm`, `${asmPath}.hack`)

// 語法解析
function parse(asmPath, i) {
    asmPath.match(/^([^\/]*)(\/.*)?$/) // 擷取要使用的程式碼（不包含註解的部分）
    var code = RegExp.$1.trim() // 將剛擷取的程式碼宣告為 code
    if (code.length == 0) return null // 比對沒有內容的字串

    // 比對 A 指令
    else if (code.slice(0, 1) == "@") {
        return { type: "A", argument: code.substring(1).trim() } // 由於第 0 個為 @ 符號，因此用 substring(1) 取出後面的內容

    // 比對 S 指令（符號）
    } else if (code.match(/^\((\w+)\)$/)) {
        return { type: "S", symbol: RegExp.$1 }

    // 比對 C 指令
    } else if (code.match(/^((([AMD]*)=)?([AMD01\+\-\&\|\!]*))(;(\w*))?$/)) {
        return { type: "C", c: RegExp.$4, d: RegExp.$3, j: RegExp.$6 }

    // 錯誤處理
    } else {
        throw `Error at line ${i}`
    }
}

function checkType(asmPath) {
    console.log("========== type ==========")
    var address = 0
    for (i = 0; i < asmPath.length; i++) {
        var p = parse(asmPath[i], i)
        if (p == null) continue // 如果沒有內容，則跳出
        
        // 如果是符號，則去符號表尋找他的位址
        else if (p == "S") {
            console.log(`symbol : ${p.symbol}`)
            symbolTable[p.symbol] = address
            continue

        // 其他則直接印出
        } else {
            console.log("p: %j", p)
        }
        console.log("%s:%s %s", intToStr(i + 1, 3, 10), intToStr(address, 4, 10), asmPath[i]);
        address++
    }
}

function convert(asmPath, hackPath) {
    console.log("==========convert==========")
    var ws = fs.createWriteStream(hackPath); // 開始寫入工作
    ws.once('open', function (fd) { // 要寫入的內容
        var address = 0;
        for (var i = 0; i < asmPath.length; i++) {
            var p = parse(asmPath[i], i); // 獲取每一行程式的 type, argument, symbol, c, d, j 指令
            if (p === null || p.type === "S") continue; // 如果是空白或符號則跳出
            var code = toCode(p); // 將每一行程式碼轉換成二進位碼
            console.log("%s:%s %s", intToStr(i + 1, 3, 10), intToStr(code, 16, 2), asmPath[i]); // 格式：行數:二進位碼 組合語言
            ws.write(intToStr(code, 16, 2) + "\n"); // 將內容寫入到暫存的檔案
            address++;
        }
        ws.end(); // 結束，將暫存檔寫入真正的檔案
    })
}

// 轉換為二進位碼
function toCode(p) {
    var address;
    // 處理 A 指令
    if (p.type === "A") {
        // 處理 A 指令的數字
        if (p.argument.match(/^\d+$/)) { // d:digit(數字)，如 @100
            address = parseInt(p.argument); // 將字串轉換成數字(如 "100" 轉換成 100)
        
        // 處理 Symbol 的標籤與變數
        } else {
            address = symbolTable[p.arg]; // 取出它的地址

            // 如果是沒見過的符號，則將它加入符號表
            if (typeof address === 'undefined') {
                address = symTop;
                addSymbol(p.argument, address);
            }
        }
        return address;

    // 處理 C 指令
    } else {
        var d = dTable[p.d];
        var c = cTable[p.c];
        var j = jTable[p.j];
        return 0b111 << 13 | c << 6 | d << 3 | j;
    }
}

function printAlignedDash(length) {
    let dash = "----"
    for (i = 0; i < length; i++) {
        dash = dash + "-"
    }
    console.log(dash)
}

function printLineNum(content, radix, length) {
    let linNum
    for (i = 0; i < content.length; i++) {
        lineNum = i.toString(radix)
        while (content.length < length) {
            lineNum = "0" + lineNum
        }
        console.log(lineNum)
    }
}

function intToStr(num, size, radix) {
    var output = num.toString(radix);
    while (output.length < size) {
        output = "0" + output;
    }
    return output;
}