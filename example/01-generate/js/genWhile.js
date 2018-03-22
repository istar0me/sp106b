var U = require('./util')
var next = U.print
var p = U.probability

// === BNF Grammar =====
// StmtList = Stmt+
// Stmt = While | Assign
<<<<<<< HEAD
// While = while (Exp) { StmtList }
=======
// While = while '(' Exp ')' { StmtList }
>>>>>>> 5d097d4e2aa0b979d674c2107aa23f7ac79f404e
// Assign = id '=' Exp
// Exp = T ([+-] T)?
// T = F ([*/] F)?
// F = [0-9a-cx-z] | (Exp)

var level = 0

function indent() {
  next(''.padStart(level * 2)) // 在開頭填充 level*2 個空白
}

function StmtList () {         // Statement List
  do {
    Stmt()
  } while (p(0.5))
}

function Stmt () {             // Statement
  if (p(0.5)) {                // 設定 5 成的機率
    While()
  } else {
    indent(); Assign()         // 縮排、賦值
  }
}

function While () {
  indent(); next('while ('); Exp(); next(') {\n')
  level ++; StmtList(); level --
  indent(); next('}\n')
}

function Assign () {
  id(); next('='); Exp(); next('\n')
}

var idList = ['x', 'y', 'z', 'a', 'b', 'c']

function id () {
  next(U.randSelect(idList))
}

function Exp () {               // While 的 Parameter
  T()
  if (p(0.5)) {
    next(U.randChar('+-'))
    T()
  }
}

function T () {
  F()
  if (p(0.5)) {
    next(U.randChar('*/'))
    F()
  }
}

function F () {
  if (p(0.7)) {
    next(U.randChar('0123456789abcxyz'))
  } else {
    next('('); Exp(); next(')')
  }
}

While()
