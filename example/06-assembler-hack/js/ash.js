var fs = require("fs");
var c  = console;
var file = process.argv[2];

// 1. Destination Table
var dtable = {
  ""   :0b000,
  "M"  :0b001,
  "D"  :0b010,
  "MD" :0b011,
  "A"  :0b100,
  "AM" :0b101,
  "AD" :0b110,
  "AMD":0b111
}

// 2. Jump Table
var jtable = {
  ""   :0b000,
  "JGT":0b001,
  "JEQ":0b010,
  "JGE":0b011,
  "JLT":0b100,
  "JNE":0b101,
  "JLE":0b110,
  "JMP":0b111
}

// 3. Compare Table
var ctable = {
  "0"   :0b0101010,
  "1"   :0b0111111,
  "-1"  :0b0111010,
  "D"   :0b0001100,
  "A"   :0b0110000, 
  "M"   :0b1110000,
  "!D"  :0b0001101,
  "!A"  :0b0110001, 
  "!M"  :0b1110001,
  "-D"  :0b0001111,
  "-A"  :0b0110011,
  "-M"  :0b1110011,
  "D+1" :0b0011111,
  "A+1" :0b0110111,
  "M+1" :0b1110111,
  "D-1" :0b0001110,
  "A-1" :0b0110010,
  "M-1" :0b1110010,
  "D+A" :0b0000010,
  "D+M" :0b1000010,
  "D-A" :0b0010011,
  "D-M" :0b1010011,
  "A-D" :0b0000111,
  "M-D" :0b1000111,
  "D&A" :0b0000000,
  "D&M" :0b1000000,
  "D|A" :0b0010101,
  "D|M" :0b1010101
}

// 4. Pre-defined (Label of) Symbol Table
var symTable = {
  "R0"  :0,
  "R1"  :1,
  "R2"  :2,
  "R3"  :3,
  "R4"  :4,
  "R5"  :5,
  "R6"  :6,
  "R7"  :7,
  "R8"  :8,
  "R9"  :9,
  "R10" :10,
  "R11" :11,
  "R12" :12,
  "R13" :13,
  "R14" :14,
  "R15" :15,
  "SP"  :0,
  "LCL" :1,
  "ARG" :2,
  "THIS":3, 
  "THAT":4,
  "KBD" :24576,
  "SCREEN":16384
};

var symTop = 16; // 由於 0~15 為保留位置，因此從 16 開始

function addSymbol(symbol) {
  symTable[symbol] = symTop;
  symTop ++;
}

assemble(file+'.asm', file+'.hack');

function assemble(asmFile, objFile) {
  var asmText = fs.readFileSync(asmFile, "utf8"); // 讀取檔案到 text 字串中
  var lines   = asmText.split(/\r?\n/); // 將組合語言分割成一行一行
  c.log(JSON.stringify(lines, null, 2)); // 轉換成 JSON 格式
  pass1(lines);
  pass2(lines, objFile);
} 

function parse(line, i) { // 語法分析（如 @2 -> { type: 'A', arg: '2' }）
  line.match(/^([^\/]*)(\/.*)?$/); // 先比對非註解，再比對註解（也可沒註解），並將結果儲存至名為 RegExp 的全域變數
  // RegExp.$1 = ([^\/]*) // 非註解的內容
  // RegExp.$2 = (\/.*) // 註解的內容
  console.log(`RegExp.$1 : ${RegExp.$1}`)
  line = RegExp.$1.trim(); // 消除非註解內容左右的空白
  if (line.length===0) // 消除空白後，若長度為0，代表為空行
    return null;
  if (line.startsWith("@")) { // 比對 A 指令（如 @i）
    return { type:"A", arg:line.substring(1).trim() } // 由於第 0 個為 @ 符號，因此用 substring(1) 取出後面的內容
  } else if (line.match(/^\((\w+)\)$/)) { // 比對符號（如 (label) ）
    // RegExp.$2 = (\w+) // 符號
    return { type:"S", symbol:RegExp.$1 }
  } else if (line.match(/^((([AMD]*)=)?([AMD01\+\-\&\|\!]*))(;(\w*))?$/)) { // 比對 C 指令（如 D=M+1, M+1;JGT）
    // RegExp.$3 = ([AMD]*) // Dest
    // RegExp.$4 = ([AMD01\+\-\&\|\!]*) // Comp
    // RegExp.$5 = (;(\w*))?$/)
    // RegExp.$6 = (\w*) // Jump
    return { type:"C", c:RegExp.$4, d:RegExp.$3, j:RegExp.$6 }
  } else {
    throw "Error: line "+(i+1);
  }
}

function pass1(lines) {
  c.log("============== pass1 ================");
  var address = 0;
  for (var i=0; i<lines.length; i++) {
    var p = parse(lines[i], i);
    if (p===null) continue;
    if (p.type === "S") { // S = Symbol
      c.log(" symbol: %s %s", p.symbol, intToStr(address, 4, 10));
      symTable[p.symbol] = address;
      c.log(symTable)
      continue;
    } else {
      c.log(" p: %j", p);
    }
    c.log("%s:%s %s", intToStr(i+1, 3, 10), intToStr(address, 4, 10),  lines[i]);
    address++;
  }
}

function pass2(lines, objFile) {
  c.log("============== pass2 ================");
  var ws = fs.createWriteStream(objFile);
  ws.once('open', function(fd) {
    var address = 0;
    for (var i=0; i<lines.length; i++) {
      var p = parse(lines[i], i);
      if (p===null || p.type === "S") continue;
      var code = toCode(p);
      c.log("%s:%s %s", intToStr(i+1, 3, 10), intToStr(code, 16, 2),  lines[i]); // 格式：行數:二進位碼 組合語言
      ws.write(intToStr(code, 16, 2)+"\n");
      address++;
    }
    ws.end();
  });
}

function intToStr(num, size, radix) {
//  c.log(" num="+num);
  var s = num.toString(radix)+"";
  while (s.length < size) s = "0" + s;
  return s;
}

function toCode(p) {
  var address; 
  if (p.type === "A") {
    if (p.arg.match(/^\d+$/)) { // d:digit(數字)，如 @100
      address = parseInt(p.arg); // 將字串轉換成數字(如 "100" 轉換成 100)
    } else { // 如 @label, @variable
      address = symTable[p.arg]; // 取出它的地址
      if (typeof address === 'undefined') {
        address = symTop;
        addSymbol(p.arg, address);
        // throw new Error(p.arg + '===undefined')
      }
    }
    return address; 
  } else { // if (p.type === "C")
    var d = dtable[p.d];
    var cx = ctable[p.c];
    console.log(`cx = ${cx}`)
    var j = jtable[p.j];
//     console.log(`${(0b111<<13).toString(2)} // 0b111<<13
// ${(cx<<6).toString(2)} // cx<<6
// ${(d<<3).toString(2)} // d<<3`)
    return 0b111<<13|cx<<6|d<<3|j;
  }
}
