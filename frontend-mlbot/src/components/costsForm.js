import React, { useState } from 'react';
import axios from 'axios';

const CostForm = ()=> {
  const [costToHire, setCostToHire] = useState('');
  const [costToExtendHours, setCostToExtendHours] = useState('');
  const [costToExtendDays, setCostToExtendDays] = useState('');
  const [intervalBetweenSlots, setIntervalBetweenSlots] = useState('');


 
    
// const submitConstraints = () => {

//     console.log("constraints button pressesd")
//     try {
//         axios.post('http://localhost:3001/api/insert/constraints',{
//           costToExtendDays: costToExtendDays,
//           costToExtendHours: costToExtendHours,
//           costToHire: costToHire,
//           intervalBetweenSlots: intervalBetweenSlots,
//         }).then(() =>{
//           alert("succesful insert constraints");
//         });}
//         catch(error){
//             console.log(error);
//         }
// }
    
    


  

  const handleSubmit = (e) => {
    e.preventDefault();

    // Store the form values in the local storage
    localStorage.setItem('costToHire', costToHire);
    localStorage.setItem('costToExtendHours', costToExtendHours);
    localStorage.setItem('costToExtendDays', costToExtendDays);
    localStorage.setItem('intervalBetweenSlots', intervalBetweenSlots);
  };

  return (
    <div>

    <form onSubmit={handleSubmit}>
      <label>
        Cost to hire new lecturer:
        <input
          type="number"
          step="100"
          min="0"
          value={costToHire}
          onChange={(e) => setCostToHire(e.target.value)}
        />
      </label>
      <br />
      <label>
        Cost to extend hours:
        <input
          type="number"
          step="100"
          min="0"
          value={costToExtendHours}
          onChange={(e) => setCostToExtendHours(e.target.value)}
        />
      </label>
      <br />
      <label>
        Cost to extend days:
        <input
          type="number"
          step="100"
          min="0"
          value={costToExtendDays}
          onChange={(e) => setCostToExtendDays(e.target.value)}
        />
      </label>
      <br />
      <label>
        Interval between slots:
        <input
          type="number"
          value={intervalBetweenSlots}
          onChange={(e) => setIntervalBetweenSlots(e.target.value)}
        />
      </label>
      <br />
      <button 
      type="submit"
    //   onClick={submitConstraints()}
      
      >Save</button>
    </form>
    </div>
  );
}

export default CostForm;