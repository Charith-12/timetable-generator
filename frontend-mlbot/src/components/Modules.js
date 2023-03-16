import React, { useState } from 'react';

class ModuleInfo{
  constructor(name, code, credits,uniqueBatch) {
    this.name = name;
    this.code = code;
    this.credits = credits;
    this.uniqueBatch = uniqueBatch;
}
}


function Modules (props) {
  const batches = JSON.parse(localStorage.getItem('batches'));
  const moduless = Array.from(batches.map(batch => batch.modules).flat());
  let modules = [...new Set(moduless)];
  // const modules = ['Module 1', 'Module 2', 'Module 3'];
  const [currentModuleIndex, setCurrentModuleIndex] = useState(0);
  const [modName, setModName] = useState('');
  const[modCode,setModCode] = useState('');
  const[credits,setCredits] = useState(0);
  const[uniqueBatch,setUniqueBatch] = useState(0);
  // const [lecturer, setLecturer] = useState([]);
  const[ModuleArray,setModuleArray] = useState([]);
  let showNextButton = false;



  


 


   const addModule = () => {
    const newMod = new ModuleInfo(modName,modCode,credits,uniqueBatch);
    return new Promise((resolve, reject) => {
    setModuleArray(prevModule => {
      const updatedModule = [...prevModule, newMod];
      localStorage.setItem('ModuleInfoArray', JSON.stringify(updatedModule));
      return updatedModule;
    } )
    localStorage.setItem('ModuleInfoArray', JSON.stringify(ModuleArray));
    setModCode('')
    setCredits(0)
    setModName('')
    setUniqueBatch(0)
    resolve();
  });

   }
  
  const handleUpdateShowNextButton = showNextButton => {
    props.onUpdateShowNextButton(showNextButton);
  };

  async function goNext(){
    await addModule();
     props.goNextfunc();
  }

  const handleNextModule = () => {
    setCurrentModuleIndex(currentModuleIndex + 1);
    addModule();
   
  };

 console.log(modules)
  return(
   
    <form>
      <h1>{modules[currentModuleIndex]}</h1>
      <label>
        Module Name:
        <input type="text" value={modName} onChange={event => setModName(event.target.value)} />
      </label>
      <br />

      <label>
        Module Code:
        <input type="text" value={modCode} onChange={event => setModCode(event.target.value)} />
      </label>

      <br />

      <label>
        Total credits:
        <input type="number" min="0" value={credits} onChange={event => setCredits(event.target.value)} />
      </label>
      <br />
      <label>
        Unique Batch
        <div>
          {batches.map((obj)=>(
            <label key={obj.id}>
              <input
                type="radio"
                name="batch"
                value={obj.name}
                checked={uniqueBatch === obj.id}
                onChange={() => setUniqueBatch(obj.id)}
      />
      {obj.name}
              
            </label>
          ))}
        </div>
      </label>
      <br/>
      {currentModuleIndex !== modules.length - 1 ? handleUpdateShowNextButton(showNextButton) : handleUpdateShowNextButton(true) }
      {(currentModuleIndex === modules.length - 1) ?
        <button type="button" onClick={goNext}>Submit</button>
         : 
        <button type="button" onClick={handleNextModule}>
          Next 
        </button>
      }




    </form>);
  
}

export default Modules;

