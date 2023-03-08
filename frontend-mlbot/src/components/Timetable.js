
import React, { useState, useEffect } from "react";
import axios from 'axios'

class TTslot {
  constructor(modules,lecturer,hour,day,classroom){
    this.modules = modules
    this.lecturer = lecturer
    this.hour = hour
    this.day = day
    this.classroom = classroom
  }
}

class BatchTT {
  constructor(name,tt){
    this.name = name 
    this.tt = tt
  }
}






function Timetable() {
  const [numHours, setNumHours] = useState(8); // default number of hours is 8
  const daysOfWeek = 
  [{number:"1",name:'monday'},
  {number:"2",name:'Tuesday'},
  {number:"3",name:'Wednesday'},
  {number:"4",name:'Thursday'},
  {number:"5",name:'Friday'},
  {number:"6",name:'Saturday'},
  {number:"7",name:'Sunday'}, ];
  const [data,setData] = useState([''])
  const [batches,setbatches] = useState([]);
  const[batchNames,setbatchNames] = useState([])


  const [timetableData, setTimetableData] = useState();


  const createBatchObjects = () =>  {
    batchNames.forEach(batchName =>{

      timetableData.forEach(element => {
        if(element.batch === batchName){
 
         let  ttslot = new TTslot(element.module,element.lecturer,element.hour,element.day,element.classroom)

         setbatches(prevBathces => [...prevBathces, new BatchTT(batchName,ttslot)])
        }     
      })
    })
  }


  const fetchTimetable = async () => {
    const response = await fetch('http://localhost:3001/api/timetable');
    const data = await response.json();
    setTimetableData(data);
    setData(data)
    createBatchObjects(data);


  let maxHour = 0;

for (let i = 0; i < data.length; i++) {
  const hour = parseInt(data[i].hour);
  if (hour > maxHour) {
    maxHour = hour;
  }
}   
setNumHours(maxHour )
   
  }



  

  const getlocal_batches = () => {
    if(localStorage.getItem('batches')){
        setbatches(JSON.parse(localStorage.getItem('batches')));
        for (let i = 0; i < batches.length; i++){
          let batch = batches[i];
          setbatchNames(batchNames => [...batchNames, batch.name])
          // batchNames.push(batch.name)
    }
}
  }









 
const runRemotePy= () => {
  fetch('http://localhost:3001/run-python')
  .then(response => response.text())
  .then(data => {
    console.log(`Received data from server: ${data}`);
    fetchTimetable()
    })
  .catch(error => {
    console.error(`Error while making request: ${error}`);
   
  });
}



  const runPyAlgo = () => {
    getlocal_batches();
    runRemotePy();
  }

return(
  <div>
  {batchNames.map(batchName => (
  <div>
    <h1>{batchName}</h1>
      <table style={{ borderCollapse: "collapse", border: "1px solid black" }}>
        <thead>
          <tr>
            <th style={{ border: "1px solid black" }}></th> {/* empty cell at top-left corner */}
            {daysOfWeek.map((day) => (
              <th key={day} style={{ border: "1px solid black" }}>
                {day.name}
              </th>
            ))}
          </tr>
        </thead>
        <tbody>
          {[...Array(numHours)].map((_, index) => (
            <tr key={index}>
              <td style={{ border: "1px solid black" }}>{index + 1}</td> {/* row label with hour number */}
              {daysOfWeek.map((day) => {
                const item = data.find((d) => d.batch === batchName && d.day ===  day.number && d.hour === (index+1).toString());
                return (
                  <td key={`${day.number}`} style={{ border: "1px solid black" }}>                    
                    {item ?  " batch: " + item.batch + " module: " + item.module + " lecturer: " + item.lecturer + " classroom: " +  item.classroom :" ------------------------------"}
                
                  </td>
                );
              })}
            </tr>
          ))}
        </tbody>
      </table>
      </div>
  ))}
      <button 
        className="button"
 >Generate with Algo 1</button>
 <button 
        className="button"
        onClick={runPyAlgo}
 >Generate with Algo 2</button>
    </div>

);


}

export default Timetable;