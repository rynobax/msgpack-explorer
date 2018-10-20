let component = ReasonReact.statelessComponent("Cell");

let make = (~header: string, ~raw: list(int), ~color: string="", _children) => {
  ...component,
  render: _self =>
    <div
      style={
        ReactDOMRe.Style.make(
          ~padding="2px",
          ~display="flex",
          ~flexDirection="column",
          ~justifyContent="center",
          ~textAlign="center",
          ~backgroundColor=color,
          ~borderWidth="1px",
          ~borderStyle="solid",
          ~borderColor="rgb(0, 0, 0, 0.2)",
          ~minWidth="64px",
          ~wordBreak="break-word",
          (),
        )
      }>
      <div
        style={
          ReactDOMRe.Style.make(
            ~borderBottomWidth="1px",
            ~borderBottomStyle="solid",
            ~borderBottomColor="rgb(0, 0, 0, 0.2)",
            (),
          )
        }>
        {ReasonReact.string(header)}
      </div>
      <div>
        {
          ReasonReact.array(
            Array.map(
              ReasonReact.string,
              Array.map(Printf.sprintf(" %02X "), Array.of_list(raw)),
            ),
          )
        }
      </div>
    </div>,
};