import DatePicker from "react-datepicker";
import "react-datepicker/dist/react-datepicker.css";
import 'react-datepicker/dist/react-datepicker-cssmodules.css';
import { useState } from "react";



const DateAdder = ({onNext}) => {
    const [startDate,setStartDate] = useState(new Date());
    const [endDate,setEndDate] = useState(new Date());
  return (
    <div className="dates">

    <div className="datesForm">
      <h3>Opening Date</h3>
      <DatePicker 
       selected={startDate} 
       onChange={(date) => setStartDate(date)} 
/>  
    </div>
    <div className="datesForm">
      <h3>Closing Date</h3>
      <DatePicker 
       selected={endDate} 
       onChange={(date) => setEndDate(date)} 
/>  
    </div> 
    </div>
  )
}

export default DateAdder