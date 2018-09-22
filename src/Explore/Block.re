let component = ReasonReact.statelessComponent("MPString");

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
          (),
        )
      }>
      <div> {ReasonReact.string(header)} </div>
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