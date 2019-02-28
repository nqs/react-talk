let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self => <div> {"Reason React!" |> ReasonReact.string} </div>,
};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));