const U = module.exports = {}

// 隨機回傳 a ~ b 的值（包含a, 不包含b）
U.rand = function (a, b) {
  return a + Math.random() * (b - a)
}

// 隨機回傳 a ~ b 間的整數（包含a, 不包含b）
// 註：採用無條件捨去法
U.randInt = function (a, b) {
  return Math.floor(a + Math.random() * (b - a))
}

// 隨機回傳陣列中的其中一個元素
U.randSelect = function (a) {
  return a[U.randInt(0, a.length)]
}

// 隨機回傳字串中的字元
// 註：由於 a.length 比 index 還多 1 ，因此就算不包含最後一個，每個元素都還是會被選到
U.randChar = function (str) {
  var len = str.length
  var i = U.randInt(0, len - 1)
  return str[i]
}

// 印出內容
// process.stdout.write() 相當於 console.log()
U.print = function (s) {
  process.stdout.write(s)
}

// 設定 p 為 0~1 的機率
U.probability = function (p) {
  return (Math.random() < p)
}