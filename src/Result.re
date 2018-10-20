let component = ReasonReact.statelessComponent("Result");

type msgpack = {. [@bs.meth] "decode": array(int) => Js.Json.t};
[@bs.module] external msgpack: msgpack = "msgpack-lite";

let make = (~dataString, _children) => {
  ...component,
  render: _self => {
    let hexList =
      Array.map(s => "0x" ++ s, Js.String.split(" ", dataString));
    let intOfStringSafe = str =>
      try (int_of_string(str)) {
      | _ => 0
      };
    let capitalHexList = Array.map(intOfStringSafe, hexList);
    let jsonStr =
      try (msgpack##decode(capitalHexList)->Js.Json.stringifyWithSpace(2)) {
      | _ => "Invalid messagepack data"
      };
    <div
      style={
        ReactDOMRe.Style.make(
          ~backgroundColor="papayawhip",
          ~width="100%",
          ~flex="1",
          ~wordBreak="break-word",
          (),
        )
      }>
      {ReasonReact.string(jsonStr)}
    </div>;
  },
};