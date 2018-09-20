let component = ReasonReact.statelessComponent("Form");

let make = (~value, ~onChange, _children) => {
  let change = event => onChange(ReactEvent.Form.target(event)##value);
  {
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
          value
          onChange=change
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
};