type state = {dataString: string};

type action =
  | DataChange(string);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {dataString: "dc 00 11 01 02 03 04 05 06 07 08 09 00 0a 0b 0c 0d 0e 0f 10"},
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