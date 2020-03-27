open SQLite;
 let db = openDatabase("test");

 let x = Database.transaction(
   db,
   t =>
     Transaction.(
       executeSql(
         t,
         "SELECT something FROM that_table",
         [`String("A string argument"), `Float(3.)],
         (_transaction, rs: resultSet({..})) => Js.log(rs),
         (_transaction, error) => Js.log(error),
       )
     )
     |> ignore,
   (_) => (),
   () => (),
 );