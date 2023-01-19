import React from 'react'
import DatePicker from "react-datepicker";
import "react-datepicker/dist/react-datepicker.css";
import 'react-datepicker/dist/react-datepicker-cssmodules.css';
import { useState } from 'react';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome'
import { faPlus } from '@fortawesome/free-solid-svg-icons'

function MyDatePicker({ initialEndDate }) {
  const [endDate, setEndDate] = useState(initialEndDate);

  return (
    <div className="inputHolidays">
   
      <DatePicker
        selected={endDate}
        onChange={(date) => setEndDate(date)}
      />
    </div>
  );
}
   

const Holidays = () => {
    // const [endDate,setEndDate] = useState(new Date());
    // const [moreHolidays,SetMoreHolidays]= useState(1);
    // // const endDates = Array(moreHolidays).fill().map((_, i) => useState(new Date()));
    // const endDates = Array(moreHolidays).fill().map(() => new Date());

    // const divs = endDates.map((endDate, i) => (
    //   <MyDatePicker key={i} initialEndDate={endDate} />
    // ));

    // const divs = endDates.map(([endDate, setEndDate], i) => (
    //   <div key={i} className="inputHolidays">
    //     <h3>Holidays</h3>
    //     <DatePicker
    //       selected={endDate}
    //       onChange={(date) => setEndDate(date)}
    //     />
    //   </div>
    // ));
  
    const [moreHolidays, setMoreHolidays] = useState(1);
    function addMore(){
      setMoreHolidays(moreHolidays + 1);
      console.log(setMoreHolidays);
    }





  const endDates = Array(moreHolidays).fill().map(() => new Date());

  const divs = endDates.map((endDate, i) => (
    <div className='holidays'>
    <MyDatePicker key={i} initialEndDate={endDate} />
    </div>
  ));

  return(
  <div className='holiday'>

<h3>Holidays</h3>


  {divs} 

  <button onClick ={addMore}>
  <FontAwesomeIcon icon={faPlus} />
  </button>
</div>
  );
}



 


export default Holidays