// import React, { useState,useEffect} from 'react'

// const LecturerForm = () => {
//     const [lecturers,setLecturers] = useState([]); 
//     const [name, setName] = useState('');
//     const[lecid,setlecid] = useState(0);
//     const [lecModules, setLecModules] = useState(['']);
//     const [maxHours, setMaxHours] = useState();
//     const [payRate,setpayRate] = useState('');
//     const [modulesArray, setmodulesArray] = useState([]);
//     const [selectedID, setselectedID] = useState(null);


//     useEffect(() => {

//         const jsonArray = localStorage.getItem('ModuleInfoArray')

//         const parsedArray = JSON.parse(jsonArray);
     
//         setmodulesArray( parsedArray);

        

//     },[])

    
//     // setmodulesArray(modulesArray => {
//     //     const jsonArray = localStorage.getItem('ModuleInfoArray')
//     //     return JSON.parse(jsonArray);
//     // });

//     function handleSelect(event){
//         setselectedID(event.target.value)
//     }

//     function handleRemove() {
//         console.log("removed:" + selectedID )
//         // const updatedArray = modulesArray.filter(obj => obj.code !== selectedID);
//         const updatedArray = modulesArray.shift();
//         setmodulesArray(updatedArray);
//         setselectedID('');
//         console.log(modulesArray)
//       }
    

//     const handleMaxHoursChange = (event) => {
//         const value = event.target.value;
//         if (value >= 0) {
//             setMaxHours(value);
//         }
//     };

//     const handleIDchange = (event) => {
//         const value = event.target.value;
//         if (value >= 0) {
//             setlecid(value);
//         }
//     };

//     const addModule = () => {
//         setLecModules([...lecModules, '']);
//     };

//     const handlepayChange = event => {
//         setpayRate(event.target.value);
//       };

//     class Lecturer {
//         constructor(name,lecid, lecModules, maxHours,payRate) {
//             this.name = name;
//             this.lecid = lecid;
//             this.lecModules = lecModules;
//             this.maxHours = maxHours;
//             this.payRate = payRate;
//         }
//     }

//     const addLecturer = () => {
//         const newLecturer = new Lecturer(name,lecid, lecModules, maxHours,payRate);
//         setLecturers(prevLecturers => {
//             const updatedLecturers = [...prevLecturers, newLecturer];
//             localStorage.setItem('lecturers', JSON.stringify(updatedLecturers));
//             return updatedLecturers;
//         });
//         console.log("add lecturer clicked");
//         console.log(newLecturer);
//         console.log(lecturers);
//         localStorage.setItem('lecturers', JSON.stringify(lecturers));
//         handleRemove();
//         setName('');
//         setLecModules([' ']);
//         setlecid(0);
//         setMaxHours(0);


//     }

//     return (
//         <div>
//             <form className='LecturerForm'>
//                 <label>
//                    Lecturer Name:
//                     <input type="text" value={name} onChange={(event) => setName(event.target.value)} />
//                 </label>
//                 <br />
//                 <label>
//                    Lecturer ID:
//                     <input type="number" value={lecid} onChange={handleIDchange} />
//                 </label>
//                 <br />
//                 <p>Teachable Modules [Module Codes]</p>
//                 {lecModules.map((lecModule, index) => (
//                     <label>
//                         Module {index + 1}
//                         <input type="text" value={lecModule} onChange={(event) => setLecModules(lecModules.map((m, i) => (i === index ? event.target.value : m)))} />
//                     </label>
//                 ))}
//                 <br />
//                 <button type="button" onClick={addModule}>
//                     Add Module
//                 </button>
//                 <br />

//               {/* Add a  unique module option */}
//                 <select value={selectedID} onChange={handleSelect}>
//         <option value="">Select a unique module</option>
//         {modulesArray.map(obj => (
//           <option key={obj.code} value={obj.code}>
//             {obj.name}
//           </option>
//         ))}
//       </select>

//       <br />

//                 <label>
//                     Maximum Working Hours:
//                     <input type="number" value={maxHours} onChange={handleMaxHoursChange} />
//                 </label>
//                 <br />
//                 <label>Pay Rate:</label>
//       <input
//         type="number"
//         step="100"
//         min="0"
//         value={payRate}
//         onChange={handlepayChange}
//       />
//             </form>
//             <button id="add lecturer" onClick={addLecturer}>Add Lecturer</button>
//         </div>
//     )
// }
// export default LecturerForm

import React, { useState, useEffect } from 'react';

const LecturerForm = () => {
  const [lecturers, setLecturers] = useState([]);
  const [name, setName] = useState('');
  const [lecid, setlecid] = useState(0);
  const [lecModules, setLecModules] = useState(['']);
  const [maxHours, setMaxHours] = useState();
  const [payRate, setpayRate] = useState('');
  const [modulesArray, setmodulesArray] = useState([]);
  const [selectedID, setselectedID] = useState(null);

  useEffect(() => {
    const jsonArray = localStorage.getItem('ModuleInfoArray');
    const parsedArray = JSON.parse(jsonArray);
    setmodulesArray(parsedArray);
  }, []);

  function handleSelect(event) {
    setselectedID(event.target.value);
  }

  function handleRemove() {
    const updatedArray = modulesArray.slice(1);
    setmodulesArray(updatedArray);
    setselectedID('');
  }

  const handleMaxHoursChange = (event) => {
    const value = event.target.value;
    if (value >= 0) {
      setMaxHours(value);
    }
  };

  const handleIDchange = (event) => {
    const value = event.target.value;
    if (value >= 0) {
      setlecid(value);
    }
  };

  const addModule = () => {
    setLecModules([...lecModules, '']);
  };

  const handlepayChange = (event) => {
    setpayRate(event.target.value);
  };

  class Lecturer {
    constructor(name, lecid, lecModules, maxHours, payRate) {
      this.name = name;
      this.lecid = lecid;
      this.lecModules = lecModules;
      this.maxHours = maxHours;
      this.payRate = payRate;
    }
  }

  const addLecturer = () => {
    const newLecturer = new Lecturer(name, lecid, lecModules, maxHours, payRate);
    setLecturers((prevLecturers) => {
      const updatedLecturers = [...prevLecturers, newLecturer];
      localStorage.setItem('lecturers', JSON.stringify(updatedLecturers));
      return updatedLecturers;
    });
    console.log('add lecturer clicked');
    console.log(newLecturer);
    console.log(lecturers);
    setName('');
    setLecModules([' ']);
    setlecid(0);
    setMaxHours(0);
    handleRemove();
  };

  return (
    <div>
      <form className='LecturerForm'>
        <label>
          Lecturer Name:
          <input type="text" value={name} onChange={(event) => setName(event.target.value)} />
        </label>
        <br />
        <label>
          Lecturer ID:
          <input type="number" value={lecid} onChange={handleIDchange} />
        </label>
        <br />
        <p>Teachable Modules [Module Codes]</p>
        {lecModules.map((lecModule, index) => (
          <label key={index}>
            Module {index + 1}
            <input
              type="text"
              value={lecModule}
              onChange={(event) =>
                setLecModules(lecModules.map((m, i) => (i === index ? event.target.value : m)))
              }
            />
          </label>
        ))}
        <br />
        <button type="button" onClick={addModule}>
          Add Module
        </button>
        <br />
        {/* Add a  unique module option */}
        <label>Select a unique module:  </label>
        <select value={selectedID} onChange={handleSelect}>
          {modulesArray.map((obj) => (
            <option key={obj.code} value={obj.code}>
              {obj.name}
            </option>
          ))}
        </select>
        <br />
        <label>
          Maximum Working Hours:
          <input type="number" value={maxHours} onChange={handleMaxHoursChange} />
        </label>
        <br />
        <label>Pay Rate:</label>
        <input type="number" step="100" min="0" value={payRate} onChange={handlepayChange} />
      </form>
      <button id="add lecturer" onClick={addLecturer}>
        Add Lecturer
      </button>
    </div>
  );
          }

export default LecturerForm