type state = {dataString: string};

type action =
  | DataChange(string);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {dataString: "93 00 01 02"},
  reducer: (action, _state) =>
    switch (action) {
    | DataChange(str) => ReasonReact.Update({dataString: str})
    },
  render: self =>
    <div
      style={
        ReactDOMRe.Style.make(
          ~backgroundColor="#ededed",
          ~width="100vw",
          ~height="100vh",
          ~display="flex",
          (),
        )
      }>
      <div
        style={
          ReactDOMRe.Style.make(
            ~width="300px",
            ~display="flex",
            ~flexDirection="column",
            (),
          )
        }>
        <Form
          value={self.state.dataString}
          onChange={str => self.ReasonReact.send(DataChange(str))}
        />
        <Result />
      </div>
      <div style={ReactDOMRe.Style.make(~flex="1", ())}>
        <Explore dataString={String.trim(self.state.dataString)} />
      </div>
    </div>,
};