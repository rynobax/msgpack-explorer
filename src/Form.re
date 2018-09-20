let component = ReasonReact.statelessComponent("Form");

let make = _children => {
  ...component,
  render: _self =>
    <div
      style={
        ReactDOMRe.Style.make(
          ~padding="10px",
          ~backgroundColor="#FFF",
          ~flex="1",
          (),
        )
      }>
      <textarea
        placeholder="msgpck hex here (a5 68 65 6c 6c 6f)"
        style={
          ReactDOMRe.Style.make(
            ~width="100%",
            ~height="100%",
            ~padding="0px",
            ~resize="none",
            ~border="none",
            ~outline="none",
            (),
          )
        }
      />
    </div>,
};