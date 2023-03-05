
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

// function Timetable() {
//   const [timetable, setTimetable] = useState([]);

//   useEffect(() => {
//     fetch('/api/timetable')
//       .then(response => response.json())
//       .then(data => setTimetable(data));
//   }, []);
  
//   return (
//     <div>
//       <h1>Timetable</h1>
//       <ul>
//         {timetable.map((row, index) => (
//           <li key={index}>
//             Batch: {row.batch}, Day: {row.day}
//           </li>
//         ))}
//       </ul>
//     </div>
//   );
// }








function Timetable() {
  const [numHours, setNumHours] = useState(8); // default number of hours is 8
  // const daysOfWeek = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"];
  const daysOfWeek = ["1", "2", "3", "4", "5", "6", "7"];
  // const [data, setData] = useState([
  //   { day: "Monday", hour: 1, value: "Task 1" },
  //   { day: "Monday", hour: 2, value: "Task 2" },
  //   { day: "Tuesday", hour: 1, value: "Task 3" },
  //   // ... other data items
  // ]);
  const [data,setData] = useState([''])
  const [batches,setbatches] = useState([]);
  const[batchNames,setbatchNames] = useState([])
  

  // 

  const [timetableData, setTimetableData] = useState();

  let listofstuff = []

  // const fetchTimetable = async () => {
  //   // try {
  //   //       const response = await fetch('/api/timetable');
  //   //       console.log("got it")
  //   //       const data = await response.json();
  //   //       console.log(data)
  //   //       setTimetableData(data);
  //   //     } catch (error) {
  //   //        console.error(error);
  //   //     }
  // }

  // const fetchTimetable = async () => {
  //   try {
  //     const response = await axios.get('http://localhost:3001/api/timetable');
  //     console.log(response.data);
  //     // do something with the data
  //   } catch (error) {
  //     console.error(error);
  //   }
  // };
  
  const createBatchObjects = () =>  {
    batchNames.forEach(batchName =>{
      // console.log(batchName)
    //   console.log(data)
    //   data.forEach(element =>{
    //     console.log(element.batch)   
    // })
      timetableData.forEach(element => {
        if(element.batch === batchName){
          // console.log(batchName)
          // data.forEach(element =>{
          // console.log(element.batch)   
          // })
         let  ttslot = new TTslot(element.module,element.lecturer,element.hour,element.day,element.classroom)
        //  console.log(ttslot.classroom)
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
  }


  // function sortData (batchname) {
  //    for d in data:
  //     if data.batchname == batchname

  // }


  // const fetchTimetable = async () => {
  //   try {
  //     const response = await fetch('/api/timetable');
  //     console.log("got it")
  //     console.log(response)
  //     const data = await response.json();
  //     // console.log(data)
  //     setTimetableData(data);
  //   } catch (error) {
  //     console.error(error);
  //   }
  // }

  // const fetchTimetable = async () => {
    
  //     const response = await fetch('/api/timetable') .then(response => response.json())
  //     .then(data => {
  //       console.log(data);
  //       // do something with the data
  //     })
  //     .catch(error => {
  //       console.error('Error:', error);
  //     });
  //   }

  // const fetchTimetable = async () => {
  //   // const response = await fetch('/api/timetable')
  //   const response = await fetch('/api/timetable', {
  //     headers: {
  //       'Accept': 'application/json'
  //     }
  //   });
  //   const data = await response.json();
  //   console.log(data);
  //   // const responseData = await response.text();
  //   // console.log("tgis is the response data")
  //   // console.log(responseData)
  //   // console.log(responseData); // check the response data
  //   // const data = JSON.parse(responseData);
  //   // console.log(data); // check the parsed data
  //   // do something with the data
  // }

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

// function getBatchTT  ()  {
//   try {
//     axios.get('http://localhost:3001/api/retrive/batchTT',{
//         batch_name : bName
//     }).then(()=>{
//       alert("succesful retived form batches");
//     });
//   } catch (error) {
//     console.log(error)
//   }
// }

// function getTT  ()  {
//   try {
//     axios.get('"/api/timetable"',{
//     }).then(()=>{
//       alert("succesful retived form batches");
//     });
//   } catch (error) {
//     console.log(error)
//   }
// }

async function  getTT () {
  // const response =  axios.get("/api/timetable");
  //   if (response.data) { // check if the data property of the response is truthy
  //     setData(response.data);
  //   } else {
  //     console.log("No data found");
  //   }

 
  // try {
  //   const response = await axios.get("/api/timetable");
  //   if (Array.isArray(response.data) && response.data.length > 0) {
  //     setData(response.data);
  //     console.log(response.data)
  //   } else {
  //     console.log("No data found");
  //   }
  // } catch (error) {
  //   console.error(error);
  // }
  
}


  

 




  function runPyAlgo(){
    console.log("              butoooooooooooooooooooooooooon")
    getlocal_batches();
    fetchTimetable();
    // createBatchObjects()
  //   const item = data.find((d) => d.day === "1" && d.hour ===  "3");
  //   {item ? console.log( item.batch ) : console.log('no')}
    
   
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
                {day}
              </th>
            ))}
          </tr>
        </thead>
        <tbody>
          {[...Array(numHours)].map((_, index) => (
            <tr key={index}>
              <td style={{ border: "1px solid black" }}>{index + 1}</td> {/* row label with hour number */}
              {daysOfWeek.map((day) => {
                const item = data.find((d) => d.batch === batchName && d.day ===  day && d.hour === (index+1).toString());
                return (
                  <td key={`${day}-${index}`} style={{ border: "1px solid black" }}>                    
                    {item ?  " batch: " + item.batch + " module: " + item.module + " lecturer: " + item.lecturer :" ------------------------------"}
                
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

//   return (
// <div>
//     {batchNames.map(batchName => (
//          <div>
//            <h1>{batchName}</h1>
//          <table style={{ borderCollapse: "collapse", border: "1px solid black" }}>
//            <thead>
//              <tr>
//                <th style={{ border: "1px solid black" }}></th> {/* empty cell at top-left corner */}
//                {daysOfWeek.map((day) => (
//                  <th key={day} style={{ border: "1px solid black" }}>
//                    {day}
//                  </th>
//                ))}
//              </tr>
//            </thead>
//            <tbody>
//              {[...Array(numHours)].map((_, index) => (
//                <tr key={index}>
//                  <td style={{ border: "1px solid black" }}>{index + 1}</td> {/* row label with hour number */}
//                  {daysOfWeek.map((day) => {
//                    const item = data.find((d) => d.day === day && d.hour === index + 1);
//                    return (
//                      <td key={`${day}-${index}`} style={{ border: "1px solid black" }}>
//                        {item ? item.value : ""}
//                      </td>
//                    );
//                  })}
//                </tr>
//              ))}
//            </tbody>
//          </table>
//        </div>
//       ))}
//       <button 
//         className="button"
//  >Generate with Algo 1</button>
//  <button 
//         className="button"
//         onClick={runPyAlgo}
//  >Generate with Algo 2</button>
//     </div>
//   );
}

export default Timetable;