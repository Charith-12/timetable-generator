import React, { useState } from 'react'

const BatchForm = () => {
    const [batches,setBatches] = useState([]); 
    const[batchName,setBatchName] = useState('');
    const[batchid,setBatchid] = useState(0);
    const[modules,setModules] = useState(['']);
    const[numStudents,setNumStudents] = useState();

    const handleNumStudentsChange = (event) => {
        const value = event.target.value;
        if (value >= 0) {
          setNumStudents(value);
        }
      };

    const addModule = () => {
        setModules([...modules, '']);
      };

      class Batch {
        constructor(name,id,modules,numStudents){
          this.name = name;
          this.id = id
          this.modules = modules;
          this.numStudents = numStudents;
        }
      }

      const addBatch = () => {
       const newBatch = new Batch(batchName,batchid,modules,numStudents);
       setBatches(prevBatches => {
        const updatedBatches = [...prevBatches, newBatch];
        localStorage.setItem('batches', JSON.stringify(updatedBatches));
        return updatedBatches;
      })
       console.log("add batch clicked");
       console.log(newBatch);
       console.log(batches);
       localStorage.setItem('batches', JSON.stringify(batches));
       setBatchName('');
       setBatchid(0);
       setModules(['']);
       setNumStudents(0);
       
      }


    return(
        <div>
        <form className='BatchForm' >
           <label>
            Batch Name:
            <input type = "text" value = {batchName} onChange={(event) => setBatchName(event.target.value)}/>
           </label>
           <br/>
           <label>
            Batch id:
            <input type = "number" min={0} value = {batchid} onChange={(event) => setBatchid(event.target.value)}/>
           </label>
           <br/>
           
           {modules.map((module,index)=>(
            <label>
                Module codes {index +1}
                <input type= "text" value={module} onChange={(event) => setModules(modules.map((m, i) => (i === index ? event.target.value : m)))} />
            </label>
           ))}
 <br/>
<button type="button"  onClick={addModule}>
        Add Module
      </button>
      <br />
      <label>
        Number of Students:
        <input type="number"  min={0} value={numStudents} onChange={handleNumStudentsChange} />
      </label>

      <br />
     
        </form>
        
        <button id ="add batch" onClick={addBatch}> Add Batch</button> 
        </div>
    )
}
export default BatchForm