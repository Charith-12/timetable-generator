const express = require("express");
const app = express();
const mysql = require('mysql2');
const bodyParser = require('body-parser');
const cors = require('cors')

const db =  mysql.createPool({
    host: "localhost",
    user: "root",
    password: "adithya889",
    database: "fypdatabase"
})

app.use(cors());
app.use(express.json());
app.use(bodyParser.urlencoded({ extended: true}));



app.post("/api/insert", (req,res) => {


    const openTime = req.body.openTime
    const closeTime = req.body.closeTime
    
    const sqlInsert = 
      "INSERT INTO movie_reviews (movieName, movieReview) VALUES (?,?)";
    db.query(sqlInsert, [openTime, closeTime], (err,result) => {
    console.log(result);
    });
    });
    

    app.post("/api/insert/batches", (req,res) => {


        const  batch_name = req.body.batch_name
        const no_students = req.body.no_students
        
        const sqlInsert = 
          "INSERT INTO batches (batch_name, no_students) VALUES (?,?)";
        db.query(sqlInsert, [batch_name, no_students], (err,result) => {
        console.log( result);
        });
        });
        
        // app.post("/api/insert/lecturers", (req,res) => {


        //     const  lec_name = req.body.lec_name
        //     const lec_id = req.body.lec_id
        //     const maxHours = req.body.maxHours
            
        //     const sqlInsert = 
        //       "INSERT INTO lecturers (lec_id,lec_name,max_hours) VALUES (?,?,?)";
        //     db.query(sqlInsert, [6,"jake",9], (err,result) => {
        //     console.log( result);
        //     });
        //     });
        
            app.post("/api/insert/lecturers", (req,res) => {

                const  lec_name = req.body.lec_name
                const lec_id = req.body.lec_id
                const maxHours = req.body.maxHours
                const payRate = parseInt(req.body.payRate)
                
                const sqlInsert = 
                  "INSERT INTO lecturers (lec_id,lec_name,max_hours,pay_rate) VALUES (?,?,?)";
                db.query(sqlInsert, [lec_id,lec_name,maxHours,payRate], (err,result) => {
                    if(err){
                        console.log(err);
                        return res.status(500).send(err);
                    }
                    console.log( result);
                    return res.status(200).send(result);
                });
                });

                app.post("/api/insert/modules", (req,res) => {

                    const  mod_code = req.body.modecode
                    const mod_name = req.body.modename
                    const credits = req.body.credits
                    
                    const sqlInsert = 
                      "INSERT INTO module (mod_code,mod_name,credits) VALUES (?,?,?)";
                    db.query(sqlInsert, [mod_code,mod_name,credits], (err,result) => {
                        if(err){
                            console.log(err);
                            return res.status(500).send(err);
                        }
                        console.log( result);
                        return res.status(200).send(result);
                    });
                    });



                    app.post("/api/insert/batch_modules", (req,res) => {

                        const batch_name = req.body.batchname
                        const module_code = req.body.module_code
                       
                        
                        const sqlInsert = 
                          "INSERT INTO batch_modules (batch_name,module_code) VALUES (?,?)";
                        db.query(sqlInsert, [batch_name,module_code], (err,result) => {
                            if(err){
                                console.log(err);
                                return res.status(500).send(err);
                            }
                            console.log( result);
                            return res.status(200).send(result);
                        });
                        });
                    
                    
                        app.post("/api/insert/lec_modules", (req,res) => {

                            const lec_id = req.body.lec_id
                            const module_code = req.body.module_code
                           
                            
                            const sqlInsert = 
                              "INSERT INTO lec_modules (lec_id,module_code) VALUES (?,?)";
                            db.query(sqlInsert, [lec_id,module_code], (err,result) => {
                                if(err){
                                    console.log(err);
                                    return res.status(500).send(err);
                                }
                                console.log( result);
                                return res.status(200).send(result);
                            });
                            });

                            app.post("/api/insert/constraints", (req,res) => {

                                const costToExtendDays = req.body.costToExtendDays
                                const costToExtendHours = req.body.costToExtendHours
                                const costToHire = req.body.costToHire
                                const intervalBetweenSlots = req.body.intervalBetweenSlots
                               
                                
                                const sqlInsert = 
                                  "INSERT INTO constraints (costToExtendDays,costToExtendHours,costToHire,intervalBetweenSlots) VALUES (?,?,?,?)";
                                db.query(sqlInsert, [costToExtendDays,costToExtendHours,costToHire,intervalBetweenSlots], (err,result) => {
                                    if(err){
                                        console.log(err);
                                        return res.status(500).send(err);
                                    }
                                    console.log( result);
                                    return res.status(200).send(result);
                                });
                                });


app.get("/",(req,res) => {-
        res.send('hello pedro');  
})

app.get('/api/timetable', async(req, res) => {
  db.query('SELECT batch,module,lecturer,hour,day,classroom FROM master_tt', (err, rows) => {
    if (err) {
      console.log(err);
      res.status(500).send('Error retrieving timetable data');
      return;
    }
    const timetable = rows.map(row => ({
      batch: row.batch,
      module: row.module,
      lecturer: row.lecturer,
      hour: row.hour,
      day: row.day,
      classroom: row.classroom
    }));
    console.log(timetable)
    res.json(timetable);
  });
});

// app.get('/api/timetable', async(req, res) => {
//   // const [rows,fields] = db.execute('SELECT * FROM batches')

//   db.query('SELECT batch, day FROM master_tt ', (err, rows) => {
//     if (err) {
//       console.log(err);
//       return;
//     }
//     // console.log(rows);
//      res.send("jfsjflkjslkjire")
//     // res.json(rows);
//   })
//   })
 // const rows =  connection.execute('SELECT * FROM master_tt');
  // res.json(rows);


app.get('/api/retrive/batchTT', (req, res) => {

     const batch_name = req

  connection.query('SELECT batch, day FROM master_tt', (error, results) => {
    if (error) {
      return res.send(error);
    } else {
      let batchTimetable = [];
      for (let i = 0; i < results.length; i++) {
        if (results[i].batch === batch_name ) {
          batchTimetable.push(results[i]);
        }
      }
      return res.json({
        data: data
      });
    }
  });
});

app.get('/api/retrive/batchNames', (req, res) => {

    const batch_name = req.body.batchname

  connection.query('SELECT * FROM batches', (error, results) => {
    if (error) {
      return res.send(error);
    } else {
      let batchNames = [];
      for (let i = 0; i < results.length; i++) {
        batchNames.push(results[i].batch_name)   
      }
      return res.json({
        data: batchNames
      });
    }
  });
});

app.listen(3001,() =>{
    console.log("running on port 3001");
});