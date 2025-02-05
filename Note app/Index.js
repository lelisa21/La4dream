const noteTitleInput = document.querySelector("#noteTitle");
const noteContentInput = document.querySelector("#noteContent");
const saveNoteButton = document.querySelector("#saveNoteButton");
const clearNotesButton = document.querySelector("#clearNotesButton");
const searchInput = document.querySelector("#searchInput");
const noteList = document.querySelector("#noteList");
const themeToggle = document.querySelector("#themeToggle");

// Load notes from localStorage
function loadNotes() {
    const notes = JSON.parse(localStorage.getItem("notes")) || [];
    notes.forEach(note => addNoteToList(note));
}

// Add note to the list
function addNoteToList(note) {
    const li = document.createElement("li");
    
    li.innerHTML = <strong>${note.title}</strong><br>${note.content};
    
    const deleteButton = document.createElement("button");
    deleteButton.textContent = "Delete";     
    deleteButton.addEventListener("click", function() {
        noteList.removeChild(li); // Remove the note when clicked
        updateLocalStorage(); // Update local storage
    });

    li.appendChild(deleteButton);
    
    noteList.appendChild(li);
}

// Save note
saveNoteButton.addEventListener("click", () => {
    const title = noteTitleInput.value.trim();
    const content = noteContentInput.value.trim();
    
    if (title === "" || content === "") return; // Prevent empty notes
    
    const newNote = { title, content };
    
    addNoteToList(newNote);
    updateLocalStorage(); // Update local storage
    noteTitleInput.value = ""; // Clear input
    noteContentInput.value = ""; // Clear input
});

// Clear all notes
clearNotesButton.addEventListener("click", () => {
    noteList.innerHTML = ""; // Clear the list
    localStorage.removeItem("notes"); // Remove from local storage
});

// Update localStorage
function updateLocalStorage() {
    const notes = Array.from(noteList.children).map(li => ({
        title: li.firstChild.innerHTML.split('<br>')[0],
        content: li.firstChild.innerHTML.split('<br>')[1],
    }));
    
    localStorage.setItem("notes", JSON.stringify(notes));
}

// Search functionality
searchInput.addEventListener("input", () => {
    const searchTerm = searchInput.value.toLowerCase();
    
    Array.from(noteList.children).forEach(li => {
        const text = li.textContent.toLowerCase();
        li.style.display = text.includes(searchTerm) ? "" : "none";
    });
});

// Theme toggle functionality
themeToggle.addEventListener("click", () => {
   document.body.classList.toggle("dark-mode"); // Toggle dark mode class on body
});

// Load notes on page load
loadNotes();
