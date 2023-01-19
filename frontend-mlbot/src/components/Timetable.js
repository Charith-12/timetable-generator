import React, { useState } from 'react';

const  Timetable = () => {
  const [days, setDays] = useState(['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday']);
  const [startTime, setStartTime] = useState('9:00am');
  const [endTime, setEndTime] = useState('5:00pm');

  const handleDayChange = (e) => {
    setDays(e.target.value);
  };

  const handleStartTimeChange = (e) => {
    setStartTime(e.target.value);
  };

  const handleEndTimeChange = (e) => {
    setEndTime(e.target.value);
  };

  return (
    <div>
      {/* <div>
        <label>Select Days:</label>
        <select value={days} onChange={handleDayChange} multiple>
          <option value='Monday'>Monday</option>
          <option value='Tuesday'>Tuesday</option>
          <option value='Wednesday'>Wednesday</option>
          <option value='Thursday'>Thursday</option>
          <option value='Friday'>Friday</option>
        </select>
      </div>
      <div>
        <label>Start Time:</label>
        <input type='time' value={startTime} onChange={handleStartTimeChange} />
      </div>
      <div>
        <label>End Time:</label>
        <input type='time' value={endTime} onChange={handleEndTimeChange} />
      </div> */}
      <table>
        <thead>
          <tr>
            <th>Day</th>
            <th>Start Time</th>
            <th>End Time</th>
          </tr>
        </thead>
        <tbody>
          {days.map((day) => (
            <tr key={day}>
              <td>{day}</td>
              <td>{startTime}</td>
              <td>{endTime}</td>
            </tr>
          ))}
        </tbody>
      </table>
      <button 
        className="button"
 >Generate with Algo 1</button>
 <button 
        className="button"
 >Generate with Algo 2</button>
    </div>
  );
}

export default Timetable;
