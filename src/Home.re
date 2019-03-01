type state = {
  isOpen: bool,
};
type action =
  | Toggle(bool);

let component = ReasonReact.reducerComponent("Home");

let make =  (~currentRoute: Router.route, _children) => {
  ...component,
  initialState: () => {
    isOpen: false,
  },
  willReceiveProps: self => {...self.state, isOpen: false},
  reducer: (action: action, _state: state) => ReasonReact.NoUpdate,
  render: self =>
    <div>
      (ReasonReact.string("Home HMR Goodness!!!!!"))
    </div>,
};