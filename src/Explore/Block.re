let component = ReasonReact.statelessComponent("MPString");

let make = (~header: string, ~raw: list(int), _children) => {
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
          /* ~borderColor="#000",
             ~borderWidth="1px",
             ~borderStyle="solid", */
          (),
        )
      }>
      <div> {ReasonReact.string(header)} </div>
      <div>
        {
          ReasonReact.array(
            Array.map(
              ReasonReact.string,
              Array.map(Printf.sprintf(" %X "), Array.of_list(raw)),
            ),
          )
        }
      </div>
    </div>,
};