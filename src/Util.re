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