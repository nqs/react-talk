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
          <h1>(ReasonReact.string("Error!"))</h1>
        </div>
      | Loading => <div> (ReasonReact.string("Loading...")) </div>
      | Loaded(weather) =>
        <div>
          <h1>(ReasonReact.string("Weather")) </h1>
          <div>
            <label>(ReasonReact.string("Temperature"))</label>
            <div>(ReasonReact.string(string_of_float(weather.temperature)))</div>
          </div>
          <div>
            <label>(ReasonReact.string("Description"))</label>
            <div>(ReasonReact.string(weather.description))</div>
          </div>
          <div>
            <button onClick=(_ => self.send(WeatherFetch))>
              (ReasonReact.string("Get Weather")) 
            </button>
          </div>
        </div>
  },
};