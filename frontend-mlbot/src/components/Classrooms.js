import React, { useState } from 'react';


const ClassroomForm = () => {
    const[roomID,setRoomID] = useState('');
    const[capacity,setCapacity] = useState(0);
    const[classrooms,setClassrooms] = useState([]);


    function addClassroom () {
        const  newClassroom = {"roomID":roomID,"capacity": capacity}
        setClassrooms(prevClassroom =>{
            const updatedClassrooms = [...prevClassroom,newClassroom]
            localStorage.setItem("classroom",JSON.stringify(classrooms))
            return updatedClassrooms
        })
        setCapacity(0);
        setRoomID("");
    }

    

    return(
        <div>
            <div>

                <label style={{margin:"1%",marginTop:"2%",}}>
                    Room ID
                    <input type="text" value={roomID} onChange={(event) => setRoomID(event.target.value)}></input>
                </label>
                
                <label>
                    Capacity
                    <input type = "number" value={capacity} min={0} onChange={(event) => setCapacity(event.target.value)}></input>
                </label>
                
                <button style={{margin:"2%"}} onClick={addClassroom}>Add Classroom</button>
            </div>
        </div>
    );
}

export default ClassroomForm