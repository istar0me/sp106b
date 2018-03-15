var U = require('./util')
var next = U.print                 // 將列印宣告給 next 變數

// === BNF Grammar =====
// E = T [+-*/] E | T
// T = [0-9] | (E)

function E () {                    // Expression
  if (U.randInt(1, 10) <= 5) {     // 有 5 成的機率執行此 block 的 statement
    T()
    next(U.randChar('+-*/'))       // 隨機從 +-*/ 選一個字元
    E()
  } else {                         // 有 5 成的機率執行此 block 的 statement
    T()
  }
}

function T () {                    // T?
  if (U.randInt(1, 10) < 7) {      // 有 7 成的機率執行此 block 的 statement
  // if (U.probability(0.7)) {     // 也可用 probability 方法改寫
    next(U.randChar('0123456789')) // 隨機從 0~9 選一個字元
  } else {                         // 有 3 成的機率執行此 block 的 statement
    next('(')
    E()
    next(')')
  }
}

for (var i = 0; i < 10; i++) {
  E()
  next('\n')
}
