// import React, { useState } from 'react';
// import App from '../App';

// const ModulesForm = () => {
 
   


//   class ModuleInfo {
//     constructor(modName,modCode, modCredit,lecturers) {
//       this.modName = modName;
//       this.modCode = modCode;
//       this.modCredit = modCredit;
//       this.lecturers = lecturers;
//     }
//   }

//   const batches = JSON.parse(localStorage.getItem('batches'));
//   const modules = Array.from(batches.map(batch => batch.modules).flat());
//   const [currentModuleIndex, setCurrentModuleIndex] = useState(0);
//   const [moduleArray, setModuleArray] = useState([]);
//   const [modName, setModName] = useState('');
//   const[modCode,setModCode] = useState('');
//   const[credits,setCredits] = useState(0);
//   const [lecturer, setLecturer] = useState([]);

//   const handleAddLecture = () => {
//     const newLecturer = [...lecturer];
//     newLecturer.push('');
//     setLecturer(newLecturer);
//   };

//   const handleLectureChange = index => event => {
//     const newLecturer = [...lecturer];
//     newLecturer[index] = event.target.value;
//     setLecturer(newLecturer);
//   };

//   const handleNextModule = () => {
//     const newModuleArray = [...moduleArray];
//     newModuleArray.push(new ModuleInfo(modName,modCode,credits,lecturer));
//     setModuleArray(newModuleArray);
//     setCurrentModuleIndex(currentModuleIndex + 1);
//   };

//   return (
//     <form>
//       <h1>{modules[currentModuleIndex]}</h1>
//       <label>
//         Module Name:
//         <input type="text" value={modName} onChange={event => setModName(event.target.value)} />
//       </label>
//       <br />

//       <label>
//         Module Code:
//         <input type="text" value={modCode} onChange={event => setModCode(event.target.value)} />
//       </label>

//       <br />

//       <label>
//         Total credits:
//         <input type="number" min="0" value={credits} onChange={event => setCredits(event.target.value)} />
//       </label>

//       {lecturer.map((lecture, index) => (
//         <div key={index}>
//           <label>
//             Lecturer {index + 1}:
//             <input type="text" value={lecture} onChange={handleLectureChange(index)} />
//           </label>
//           <br />
//         </div>
//       ))}
//       <button type="button" onClick={handleAddLecture}>
//         Add Lecture
//       </button>
//       <br />
//       {(currentModuleIndex === modules.length) ?<button type="button" onClick={handleNextModule}>
//         Next 
//       </button> : <></> }
      
//     </form>
//   );
// };

// export default ModulesForm;
