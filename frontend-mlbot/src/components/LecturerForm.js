import React, { useState, useEffect } from 'react';

const LecturerForm = () => {
  const [lecturers, setLecturers] = useState([]);

  //lecmods is different from lecModules. lecmods contains the unique lecture for a module. 
  //The reason for this is the edge coloring algorithm is assumes a 1:M mapping of lecturers and modules
  // while the graph theory based greedy alogrithm assumes a M:M mapping. 
  const [lecmods, setlecmods] = useState([]);
  const [name, setName] = useState('');
  const [lecid, setlecid] = useState('');
  const [lecModules, setLecModules] = useState([]);
  const [maxHours, setMaxHours] = useState();
  const [payRate, setpayRate] = useState('');
  const [uniqueModulesArray, setuniquemodulesArray] = useState([]);
  const [modulesArray,setmodulesArray] = useState([]);
  const [modules,setmodules] = useState([]);
  const [selectedIDs, setSelectedIDs] = useState([]);

  useEffect(() => {
    const jsonArray = localStorage.getItem('ModuleInfoArray');
    const parsedArray = JSON.parse(jsonArray);
    setmodulesArray(parsedArray);
    setuniquemodulesArray(parsedArray);
  }, []);

  const handleSelect = (event) => {
    const id = event.target.value;
    if (event.target.checked) {
      setSelectedIDs([...selectedIDs, id]);
    } else {
      setSelectedIDs(selectedIDs.filter((selectedID) => selectedID !== id));
    }
  };

  const handleModulesSelect = (event) => {
    const id = event.target.value;
    if (event.target.checked) {
      setLecModules([...lecModules,id])
    } else {
      setLecModules(selectedIDs.filter((selectedID) => selectedID !== id));
    }
  }

  const handleRemove = () => {
    const updatedArray = uniqueModulesArray.filter(
      (obj) => !selectedIDs.includes(obj.code)
    );
    setuniquemodulesArray(updatedArray);
    setSelectedIDs([]);
  };

  const handleMaxHoursChange = (event) => {
    const value = event.target.value;
    if (value >= 0) {
      setMaxHours(value);
    }
  };

  // const handleIDchange = (event) => {
  //   const value = event.target.value;
  //   if (value >= 0) {
  //     setlecid(value);
  //   }
  // };

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

  // for the c timetable
  class lecmodAlloc{
    constructor(lec,mod){
      this.lec  = lec;
      this.mod = mod;
    }

  }

  const addlecmodAlloc = (lec,mods) => {
    mods.map((mod)=>{
      const newlecmod = new lecmodAlloc(lec,mod)
       setlecmods((prevlecmods) => {
        const updatedlecmods = [...prevlecmods,newlecmod];
        localStorage.setItem('lecmodalloc',JSON.stringify(updatedlecmods));
        return updatedlecmods;
       })
    }) 
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
  
    addlecmodAlloc(lecid,selectedIDs);
    setName('');
    setLecModules([]);
    setlecid('');
    setMaxHours(0);
    handleRemove();

    const checkboxes = document.querySelectorAll('.module-code-checkbox');

// Loop through the checkboxes and set their checked property to false
checkboxes.forEach((checkbox) => {
  checkbox.checked = false;
});
  };

  return (
    <div>
      <form className="LecturerForm">
        <label>
          Lecturer Name:
          <input
            type="text"
            value={name}
            onChange={(event) => setName(event.target.value)}
          />
        </label>
        <br />
        <label>
          Lecturer ID:
          <input type="text" value={lecid} onChange={(event) => setlecid(event.target.value)} />
        </label>
        <br />
        <p>Teachable Modules [Module Codes]</p>



{modulesArray.map((obj) => (
    <label key={obj.code}>
      <input
        class="module-code-checkbox"
        type="checkbox"
        value={obj.code}
        onChange={handleModulesSelect}
      />
      {obj.name}
    </label>
  ))}
  
        {/* {lecModules.map((lecModule, index) => (
          <label key={index}>
            Module {index + 1}
            <input
              type="text"
              value={lecModule}
              onChange={(event) =>
                setLecModules(
                  lecModules.map((m, i) => (i === index ? event.target.value : m))
                )
              }
            />
          </label>
        ))} */}
        <br />
        <button type="button" onClick={addModule}>
          Add Module
        </button>
        <br />
        {/* Add a unique module option */}
        <label>Select unique modules: </label>
        <div>
  {uniqueModulesArray.map((obj) => (
    <label key={obj.code}>
      <input
        type="checkbox"
        value={obj.code}
        checked={selectedIDs.includes(obj.code)}
        onChange={handleSelect}
      />
      {obj.name}
    </label>
  ))}
</div>
        {/* <select multiple value={selectedIDs} onChange={handleSelect}>
          {modulesArray.map((obj) => (
            <option key={obj.code} value={obj.code}>
              {obj.name}
            </option>
          ))}
        </select> */}
        <br />
        <label>
          Maximum Working Hours:
          <input type="number" value={maxHours} onChange={handleMaxHoursChange} />
        </label>
        <br />
        <label>Pay Rate:</label>
        <input
          type="number"
          step="100"
          min="0"
          value={payRate}
          onChange={handlepayChange}
        />
      </form>
      <button id="add-lecturer" onClick={addLecturer}>
        Add Lecturer
      </button>
      {/* <button id="remove-modules" onClick={handleRemove}>
        Remove Selected Modules
      </button> */}
    </div>
  );
          }  

export default LecturerForm