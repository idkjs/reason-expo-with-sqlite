open ReactNative;
open Expo;

type doneHeading = string;
let statusBarHeight = Constants.statusBarHeight->float_of_int->Obj.magic;
let styles =
  Style.(
    StyleSheet.create({
  "container": style(
    ~backgroundColor="#fff",
    ~flex=1.,
    ~paddingTop=statusBarHeight,
          (),
        ),
  "heading": style(
    ~fontSize=20.,
    ~fontWeight=`bold,
    ~textAlign=`center,
          (),
        ),
  "flexRow": style(
    ~flexDirection= `row,
          (),
        ),
  "input": style(
    ~borderColor="#4630eb",
    ~borderRadius=4.,
    ~borderWidth=1.,
    ~flex=1.,
    ~height=48.->dp,
    ~margin=16.->dp,
    ~padding=8.->dp,
          (),
        ),
  "listArea": style(
    ~backgroundColor= "#f0f0f0",
    ~flex= 1.,
    ~paddingTop= 16.->dp,
          (),
        ),
  "sectionContainer": style(
    ~marginBottom= 16.->dp,
    ~marginHorizontal= 16.->dp,
          (),
        ),
  "sectionHeading": style(
    ~fontSize=18.,
    ~marginBottom=8.->dp,
          (),
        ),
  }));
  open SQLite;
    let db = openDatabase("db.db");
let items = (done_: doneHeading, onPressItem ) => {
  let (items, setItems) = React.useState(()=> None);
  React.useEffect0(() => {
    open Transaction;
    let tx =(t)=> Js.Promise.resolve(executeSql(
         t,
         "select * from items where done = ?;",
         [done_ ? `Float(1.) : `Float(0.)],
         (_transaction, rs: resultSet({..})) => Js.log(rs),
         (_transaction, error) => Js.log(error),
       ))|> ignore
 
 Database.transaction(
   db,
   t =>(tx(t)),
 );
   None

});

 
  // React.useEffect(() => {
  //   db.transaction(tx => {
  //     tx.executeSql(
  //       `select * from items where done = ?;`,
  //       [doneHeading ? 1 : 0],
  //       (_, { rows: { _array } }) => setItems(_array)
  //     );
  //   });
  // }, []);

  let heading = doneHeading ? "Completed" : "Todo";

  if (items === null || items.length === 0) {
    return null;
  }

  return (
    <View style={styles.sectionContainer}>
      <Text style={styles.sectionHeading}>{heading}</Text>
      {items.map(({ id, done_, value }) => (
        <TouchableOpacity
          key={id}
          onPress={() => onPressItem && onPressItem(id)}
          style={{
            backgroundColor: done_ ? "#1c9963" : "#fff",
            borderColor: "#000",
            borderWidth: 1,
            padding: 8
          }}
        >
          <Text style={{ color: done_ ? "#fff" : "#000" }}>{value}</Text>
        </TouchableOpacity>
      ))}
    </View>
  );
};
[@react.component]
let app = () => {
  <View style=styles##container>
    <LinearGradient
      colors=[|"#DD4B39", "#C62C19"|]
      start=[|0.0, 0.0|]
      _end=[|1.0, 1.0|]
      style=Style.(style(~padding=dp(12.), ~borderRadius=12., ()))>
      <Text style=styles##instructions>
        {React.string("To get started, edit App.re")}
      </Text>
    </LinearGradient>
  </View>;
};