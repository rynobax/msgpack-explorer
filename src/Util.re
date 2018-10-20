let splitAt = (list, n) => {
  let len = List.length(list);
  let min = len - n;
  let rec fn = (x, hd, tl) =>
    switch (x) {
    | 0 => (List.rev(hd), List.rev(tl))
    | _ when x > min => fn(x - 1, [List.nth(list, len - x), ...hd], tl)
    | _ => fn(x - 1, hd, [List.nth(list, len - x), ...tl])
    };
  fn(len, [], []);
};

let addSign = (value: int64, nBits: int) => {
  Js.log(value->Int64.to_string);
  let max = Int64.of_float(2.0 ** nBits->float_of_int);
  let middle = Int64.div(max, Int64.of_int(2));
  Js.log(middle->Int64.to_string);
  if (value >= middle) {
    Int64.sub(value, max)->Int64.to_string;
  } else {
    value->Int64.to_string;
  };
};

let hex_of_int_list = (l: list(int)) =>
  "0x" ++ String.concat("", List.map(Printf.sprintf("%02X"), l));

let parseFloat: array(int) => float = [%bs.raw
  {|
  function (arr) {
    const bops = require('bops');
    const b = bops.from(arr);
    console.log(arr.length)
    if(arr.length === 4) {
      return bops.readFloatBE(b);
    } else if(arr.length === 8) {
      return bops.readDoubleBE(b);
    } else {
      return NaN;
    }
  }
|}
];