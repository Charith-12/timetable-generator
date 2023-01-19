import React, { useState } from 'react';
import axios from 'axios'


function TimeForm() {
  const [openTime, setOpenTime] = useState('');
  const [closeTime, setCloseTime] = useState('');

  function submitDB(){
    axios.post('http://localhost:3001/api/insert',{
      openTime: openTime,
      closeTime: closeTime,
    }).then(() =>{
      alert("succesful insert");
    });
  }


  function handleSave() {
    localStorage.setItem('openTime', openTime);
    localStorage.setItem('closeTime', closeTime);
    submitDB();
  }

  return (
    <form>
      <label>
        Open Time:
        <input type="time" value={openTime} onChange={e => setOpenTime(e.target.value)} />
      </label>
      <br />
      <label>
        Close Time:
        <input type="time" value={closeTime} onChange={e => setCloseTime(e.target.value)} />
      </label>
      <br />
      <button type="button" onClick={handleSave}>
        Save
      </button>
    </form>
  );
}

export default TimeForm;