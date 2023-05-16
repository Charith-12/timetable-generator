
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
  const time = new Date(); 
  const [startTime,setStartTime] = useState(0);
  const [endTime,setEndTime] = useState(0);
  const[ al,setAl] = useState('none')


  const [timetableData, setTimetableData] = useState();
  const [edgeData,setEdgeDatas] = useState([{
    lec_id: 'Ltest',
    mod_id: 'EMNTest',
    batch_id: 2,
    timeSlot: 6,
    room_id: 'FF2'    
  }]);


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


//   let maxHour = 0;

// for (let i = 0; i < data.length; i++) {
//   const hour = parseInt(data[i].hour);
//   if (hour > maxHour) {
//     maxHour = hour;
//   }
// }   
setNumHours(24 -startTime)
   
  }

  const fetchEdges = async () => {
    const response = await fetch('http://localhost:3001/api/edges');
    const data = await response.json();
    setEdgeDatas(data);
    console.log(edgeData)
    setNumHours(endTime - startTime);

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

  const getStartTime = () => {
    const timeValue = localStorage.getItem('openTime'); 
    time.setHours(timeValue.slice(0, 2)); 
    time.setMinutes(timeValue.slice(3)); 
    setStartTime(time.getHours())
    console.log("heres the start hour:    " + time.getHours())
  }

  const getEndtime = () => {
    const timeValue = localStorage.getItem('closeTime');
    time.setHours(timeValue.slice(0,2));
    time.setMinutes(timeValue.slice(3));
    setEndTime(time.getHours());
    console.log("heres the end time:    " + time.getHours())
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

const runRemoteC = () => {
  fetch('http://localhost:3001/run-c')
  .then(response => response.text())
  .then(data => {
    console.log(`Received data from  unverstiy(c) server: ${data}`);
    fetchEdges();
    })
  .catch(error => {
    console.error(`Error while making request form unviversity(c server): ${error}`);
   
  });
}



  const runPyAlgo = () => {
    setAl("Py");
    getStartTime();
    getlocal_batches();
    runRemotePy();
  }

  const runCAlgo =  () =>{
    setAl("C");
    getStartTime();
    getEndtime();
    getlocal_batches();
    runRemoteC();
  }

  if (al === "Py") {
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
              <td style={{ border: "1px solid black" }}>{ startTime +  index  }</td> {/* row label with hour number */}
              {daysOfWeek.map((day) => {
                const item = data.find((d) => d.batch === batchName && d.day ===  day.number && d.hour === (startTime + index).toString());
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
        onClick={runCAlgo}
 >Generate with Algo 1</button>
 <button 
        className="button"
        onClick={runPyAlgo}
 >Generate with Algo 2</button>
    </div>

);
  } else if(al === 'C'){

    return(

      <div>
      {batches.map(batch=> (
      <div>
        <h1>{batch.id}</h1>
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
                  <td style={{ border: "1px solid black" }}>{ startTime +  index  }</td> {/* row label with hour number */}
                  {daysOfWeek.map((day) => {
                    const item = edgeData.find((d) => d.batch_id.toString() === batch.id && (d.timeSlot - (numHours * (day.number-1))) === (index + 1));
                    // const item = edgeData.find((d) => d.batch_id.toString() === batch.id);
                    // && (d.timeSlot - (numHours * (day.number-1))) === index + 1
                    // const item = edgeData[0] ;
                    return (
                      <td key={`${day.number}`} style={{ border: "1px solid black" }}>    
                      {/* {item ?  " batch id: " + item.batch_id.toString() :" ------------------------------"}                 */}
                        {item ?  " batch id: " + item.batch_id.toString() + " module: " + item.mod_id + " lecturer: " + item.lec_id + " classroom: " +  item.room_id :" ------------------------------"}
                       {/* { "gr"} */}
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
            onClick={runCAlgo}
     >Generate with Algo 1</button>
     <button 
            className="button"
            onClick={runPyAlgo}
     >Generate with Algo 2</button>
        </div>
    );

  }else{
   return(
    <div>
            <button 
        className="button"
        onClick={runCAlgo}
 >Generate with Algo 1</button>
 <button 
        className="button"
        onClick={runPyAlgo}
 >Generate with Algo 2</button>
    </div>
   );
  }

 




}

export default Timetable;