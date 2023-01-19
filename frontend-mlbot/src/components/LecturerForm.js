import React, { useState } from 'react'

const LecturerForm = () => {
    const [lecturers,setLecturers] = useState([]); 
    const [name, setName] = useState('');
    const[lecid,setlecid] = useState(0);
    const [lecModules, setLecModules] = useState(['']);
    const [maxHours, setMaxHours] = useState();
    const [payRate,setpayRate] = useState('');

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

    const handlepayChange = event => {
        setpayRate(event.target.value);
      };

    class Lecturer {
        constructor(name,lecid, lecModules, maxHours,payRate) {
            this.name = name;
            this.lecid = lecid;
            this.lecModules = lecModules;
            this.maxHours = maxHours;
            this.payRate = payRate;
        }
    }

    const addLecturer = () => {
        const newLecturer = new Lecturer(name,lecid, lecModules, maxHours,payRate);
        setLecturers(prevLecturers => {
            const updatedLecturers = [...prevLecturers, newLecturer];
            localStorage.setItem('lecturers', JSON.stringify(updatedLecturers));
            return updatedLecturers;
        });
        console.log("add lecturer clicked");
        console.log(newLecturer);
        console.log(lecturers);
        localStorage.setItem('lecturers', JSON.stringify(lecturers));
        setName('');
        setLecModules([' ']);
        setlecid(0);
        setMaxHours(0);
    }

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
                <p>Teachable Modules</p>
                {lecModules.map((lecModule, index) => (
                    <label>
                        Module {index + 1}
                        <input type="text" value={lecModule} onChange={(event) => setLecModules(lecModules.map((m, i) => (i === index ? event.target.value : m)))} />
                    </label>
                ))}
                <br />
                <button type="button" onClick={addModule}>
                    Add Module
                </button>
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
            <button id="add lecturer" onClick={addLecturer}>Add Lecturer</button>
        </div>
    )
}
export default LecturerForm
