[@bs.val] external require : string => string = "";
[@bs.val] [@bs.scope "performance"] external now : unit => float = "";

type touches = {
  first: option((float, float)),
  last: option((float, float)),
};

type state = {
  isOpen: bool,
  touches,
  width: ref(float),
};

type action =
  | ToggleMenu(bool)
  | TouchStart(float)
  | TouchMove(float)
  | TouchEnd;

let component = ReasonReact.reducerComponent("App");

let make = (~currentRoute: Router.route, _children) => {
  ...component,
  initialState: () => {
    isOpen: false,
    touches: {
      first: None,
      last: None,
    },
    width: ref(0.0),
  },
  willReceiveProps: self => {...self.state, isOpen: false},
  reducer: (action, state) =>
    switch (action) {
    | ToggleMenu(isOpen) => ReasonReact.Update({...state, isOpen})
    | TouchStart(clientX) =>
      if (state.isOpen) {
        ReasonReact.Update({
          ...state,
          touches: {
            first: Some((clientX, now())),
            last: None,
          },
        });
      } else {
        ReasonReact.NoUpdate;
      }
    | TouchMove(clientX) =>
      if (state.isOpen) {
        ReasonReact.Update({
          ...state,
          touches: {
            ...state.touches,
            last: Some((clientX, now())),
          },
        });
      } else {
        ReasonReact.NoUpdate;
      }
    | TouchEnd =>
      if (state.isOpen) {
        let (x, t) =
          Belt.Option.getWithDefault(state.touches.first, (0.0, 0.0));
        let (x', t') =
          Belt.Option.getWithDefault(state.touches.last, (0.0, 0.0));
        let velocity = (x' -. x) /. (t' -. t);
        let state = {
          ...state,
          touches: {
            first: None,
            last: None,
          },
        };
        if (velocity < (-0.3) || x' < state.width^ /. 2.0) {
          ReasonReact.UpdateWithSideEffects(
            state,
            (self => self.send(ToggleMenu(false))),
          );
        } else {
          ReasonReact.Update(state);
        };
      } else {
        ReasonReact.NoUpdate;
      }
    },
  render: self =>
    <div>
      <header>
        <h1> (ReasonReact.string(currentRoute.title)) </h1>
      </header>
      <nav>
        <header>
        </header>
        <label> (ReasonReact.string("home label")) </label>
        <ul>
          <li>
            <Router.NavLink href="/">
              (ReasonReact.string("Home"))
            </Router.NavLink>
          </li>
        </ul>
        <label> (ReasonReact.string("pages")) </label>
        <ul>
          <li>
            <Router.NavLink href="/page1">
              (ReasonReact.string("Page1"))
            </Router.NavLink>
          </li>
          <li>
            <Router.NavLink href="/page2">
              (ReasonReact.string("Page2"))
            </Router.NavLink>
          </li>
          <li>
            <Router.NavLink href="/page3">
              (ReasonReact.string("Page3"))
            </Router.NavLink>
          </li>
        </ul>
      </nav>
      <main>
        currentRoute.component
      </main>
    </div>,
};
