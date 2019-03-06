type state =
  | Loading
  | Error
  | Loaded(WeatherDecoder.weather);

type action =
  | WeatherFetch
  | WeatherFetched(WeatherDecoder.weather)
  | WeatherFailedToFetch;

let component = ReasonReact.reducerComponent("Home");

let make =  _children => {
  ...component,
  initialState: _state => Loading,
  didMount: self => self.send(WeatherFetch),
  reducer: (action, _state) =>
    switch (action) {
    | WeatherFetch =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
            Js.Promise.(
              Axios.get("https://api.weather.gov/gridpoints/PBZ/77,65/forecast")
              |> then_(response =>
                response##data |> WeatherDecoder.decodeWeatherResponse
                |> weatherResponse => weatherResponse.properties.periods
                  |> List.hd
                |> weather => self.send(WeatherFetched(weather))
                |> resolve
              )
              |> catch(error => self.send(WeatherFailedToFetch) |> resolve)
              |> ignore
            )
        ),
      )
    | WeatherFetched(weather) => ReasonReact.Update(Loaded(weather))
    | WeatherFailedToFetch=> ReasonReact.Update(Error)
  },
  render: self =>
    switch (self.state) {
      | Error=>
        <div>
          <h1>("Error!" |> ReasonReact.string)</h1>
        </div>
      | Loading => <div> ("Loading..." |> ReasonReact.string) </div>
      | Loaded(weather) =>
        <div className="jumbotron">
          <h1 className="display-4">("Weather" |> ReasonReact.string) </h1>
          <p className="lead">("This will fetch the weather for Pittsburgh" |> ReasonReact.string)</p>
          <p>(weather.description |> ReasonReact.string)</p>
          <button className="btn btn-primary" onClick=(_ => self.send(WeatherFetch))>
            ("Get Weather" |> ReasonReact.string)
          </button>
        </div>
  },
};