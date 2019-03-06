let component = ReasonReact.statelessComponent("Page1");

let make = _children => {
  ...component,
  render: _self =>
    <div className="Page1">
      <h1>("Page1" |> ReasonReact.string)</h1>
    </div>,
};