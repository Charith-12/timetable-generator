const express = require("express");
const app = express();
const mysql = require('mysql');
const bodyParser = require('body-parser');
const cors = require('cors')

const fypdb =  mysql.createPool({
  host: "localhost",
  user: "username",
  password: "password",
  database: "fypdatabase"
})

const university = mysql.createPool({
  host: "localhost",
  user: "root",
  password: "adithya1",
  database: "university"
})



app.use(cors());
app.use(express.json());
app.use(bodyParser.urlencoded({ extended: true}));


// university.getConnection((err, connection) => {
//   if (err) {
//     console.error("Error connecting to database: ", err);
//   } else {
//     console.log("Connected to database successfully!");
//     // test the database connection by running a sample query
//     connection.query("SELECT * FROM batches", (err, results, fields) => {
//       if (err) {
//         console.error("Error querying database: ", err);
//       } else {
//         console.log("Query result: ", results);
//       }
//       // release the connection back to the pool
//       connection.release();
//     });
//   }
// });



app.post("/api/insert", (req,res) => {


    const openTime = "bee";
    const closeTime = "good";
    
    const sqlInsert = 
      "INSERT INTO moviereviews (name, review) VALUES (?,?)";
      try {
        university.query(sqlInsert, [openTime, closeTime], (err,result) => {
          console.log(result);
          res.send("Done")
          });
      } catch (error) {
        res.send(error)
      }
    
    
    });
    

app.post("/api/insert/batches", (req, res) => {
  const batch_name = req.body.batch_name;
  const batchid = req.body.batchid;
  const no_students = req.body.no_students;

  const sqlInsert1 = "INSERT INTO batches (batch_name, no_students, batchid) VALUES (?,?,?)";
  const sqlInsert2 = "INSERT INTO batches (batch_name, no_students, batch_id) VALUES (?,?,?)";
  // uploads to fypdatabase for python algorithm
  fypdb.query(sqlInsert1, [batch_name, no_students, batchid], (err, result) => {
    if (err) {
      console.log(err);
      res.status(500).send(err);
    } else {
      console.log(result);
      //uploads to university database for c algorithm
      university.query(sqlInsert2, [batch_name, no_students, batchid], (err, result) => {
        if (err) {
          console.error(err);
          res.status(500).send(err);
        } else {
          console.log(result);
          res.status(200).send(result);
        }
      });
    }
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

    const lec_name = req.body.lec_name
    const lec_id = req.body.lec_id
    const maxHours = req.body.maxHours
    const payRate = req.body.payRate
    
    const sqlInsert1 = 
      "INSERT INTO lecturers (lec_id,lec_name,max_hours,pay_rate) VALUES (?,?,?,?)";
    
    const sqlInsert2 = 
      "INSERT INTO lecturers (lec_id,lec_name,no_subjects,wl) VALUES (?,?,?,?)";



    fypdb.query(sqlInsert1, [lec_id,lec_name,maxHours,payRate], (err,result) => {
        if(err){
            console.error(err);
            return res.status(500).send(err);
        }else{
          console.log(result);
          university.query(sqlInsert2,[lec_id,lec_name,0,0],(err,result) => {
            if(err){
              console.error(err);
              return res.status(500).send(err);
            }else{
              console.log(result);
              return res.status(200).send(result);
            }
          })
        }
    });
    });

app.post("/api/insert/modules", (req,res) => {

    const  mod_code = req.body.modecode
    const mod_name = req.body.modename
    const credits = req.body.credits
    const batch_id = req.body.batch
    
    const sqlInsert1 = 
      "INSERT INTO module (mod_code,mod_name,credits) VALUES (?,?,?)";

    const sqlInsert2 =
      "INSERT INTO modules (mod_id,mod_name,credits,batch_id) VALUES (?,?,?,?)";

    fypdb.query(sqlInsert1, [mod_code,mod_name,credits], (err,result) => {
        if(err){
        console.error(err)
        return res.status(500).send(err);
        }else{
          console.log("sent to fypdatabase module table" + result);
          university.query(sqlInsert2,[mod_code,mod_name,credits,batch_id],(err,result) => {
            if(err){
              console.error(err);
              return res.status(500).send(err);
            }else{
              console.log("sent to university database modules table" + result);
              return res.status(200).send(result);
            }
          })
        }
    });
    });



app.post("/api/insert/batch_modules", (req,res) => {

  const batch_name = req.body.batchname
  const module_code = req.body.module_code
  const batchid = req.body.batchid
  
  
  const sqlInsert = 
    "INSERT INTO batch_modules (batch_name,module_code,batchid) VALUES (?,?,?)";
  fypdb.query(sqlInsert, [batch_name,module_code,batchid], (err,result) => {
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
    fypdb.query(sqlInsert, [lec_id,module_code], (err,result) => {
        if(err){
            console.log(err);
            return res.status(500).send(err);
        }
        console.log( result);
        return res.status(200).send(result);
    });
    });

app.post("/api/insert/lmalloc",(req,res) => {

    const lec_id = req.body.lec_id;
    const mod_id = req.body.mod_id;

    const sqlInsert =
    "INSERT INTO lmallocations (lec_id,mod_id) VALUES(?,?)";

    university.query(sqlInsert,[lec_id,mod_id], (err,result) => {
      if(err){
        console.error(err);
        return res.status(500).send(err)
      }else{
        console.log("sent to lmallocations table in university database");
        return res.status(200).send(result);
      }
    })

}
)

app.post("/api/insert/classrooms",(req,res) => {
  
  const room_id = req.body.room_id;
  const capacity = req.body.capacity;
  


  const sqlInsert = "INSERT INTO classrooms (room_id,capacity) VALUES(?,?)";
  fypdb.query(sqlInsert,[room_id,capacity],(err,result)=>{
    if(err){
      console.log(err);
      return res.status(500).send(err)
    }else{
      console.log(result)
      console.log("succesfully interted classroom in fyp database ");
      university.query(sqlInsert,[room_id,capacity],(err,result) =>{
        if(err){
          console.error(err)
          return res.status(500).send(err)
        }else{
          console.log("succesfully interted classroom in university database ");
          return res.status(200).send(result)
        }
      })
    }
  })
})

app.post("/api/insert/constraints", (req,res) => {

  const costToExtendDays = req.body.costToExtendDays
  const costToExtendHours = req.body.costToExtendHours
  const costToHire = req.body.costToHire
  const intervalBetweenSlots = req.body.intervalBetweenSlots
  const openTime = req.body.openTime
  const closeTime = req.body.closeTime
  
  
  const sqlInsert = 
    "INSERT INTO constraints (costToExtendDays,costToExtendHours,costToHire,intervalBetweenSlots,openTime,closeTime) VALUES (?,?,?,?,?,?)";
  fypdb.query(sqlInsert, [costToExtendDays,costToExtendHours,costToHire,intervalBetweenSlots,openTime,closeTime], (err,result) => {
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
  fypdb.query('SELECT batch,module,lecturer,hour,day,classroom FROM master_tt', (err, rows) => {
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

app.get('/api/edges',async(req,res) => {
  university.query('SELECT lec_id,mod_id,batch_id,timeSlot,room_id FROM edges',(err,rows) => {
    if(err){
      console.error(err);
     return res.status(500).send(err);
    }else{
      const edges = rows.map((row) => ({
        lec_id: row.lec_id,
        mod_id: row.mod_id,
        batch_id: row.batch_id,
        timeSlot: row.timeSlot,
        room_id: row.room_id
      }));
      console.log(edges);
      res.json(edges);
    }
  })
})

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


const { spawn } = require('child_process');



app.get('/run-python', (req, res) => {
  const pythonProcess = spawn('python3', ['algoData.py']);

  pythonProcess.stdout.on('data', (data) => {
    console.log(`stdout: ${data}`);
  });

  pythonProcess.stderr.on('data', (data) => {
    console.error(`stderr: ${data}`);
  });

  pythonProcess.on('close', (code) => {
    console.log(`child process exited with code ${code}`);
    res.send(`Python script executed with code ${code}`);
  });
});



app.get('/run-c', (req, res) => {
  const { exec } = require('child_process');

exec('gcc setEdgeCols.c -o cProgram && ./cProgram', (error, stdout, stderr) => {
  if (error) {
    console.error(`Compilation error: ${error.message}`);
    return;
  }
  if (stderr) {
    console.error(`Runtime error: ${stderr}`);
    return;
  }
  console.log(`Program output: ${stdout}`);
});

});



app.listen(3001,() =>{
  console.log("running on port 3001");
});


