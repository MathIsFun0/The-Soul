function decrementRerollNumber() {
    document.getElementById("reroll-input").value--;
    if (document.getElementById("reroll-input").value<1) document.getElementById("reroll-input").value=1;
}

function incrementRerollNumber() {
    document.getElementById("reroll-input").value++;
    if (document.getElementById("reroll-input").value > 999) {
        document.getElementById("reroll-input").value = 999;
    }
}
window.addEventListener('DOMContentLoaded', () => {
document.getElementById("reroll-input").addEventListener('input', () => {
    document.getElementById("reroll-input").value = parseInt(document.getElementById("reroll-input").value)
    if (document.getElementById("reroll-input").value < 1) {
        document.getElementById("reroll-input").value = 1;
    } else if (document.getElementById("reroll-input").value > 999) {
        document.getElementById("reroll-input").value = 999;
    }
    if (isNaN(document.getElementById("reroll-input").value)) {
        document.getElementById("reroll-input").value = 1;
    }
});
});
function openSettings() {
    var settingsMenu = document.getElementById("settings");
    var overlay = document.getElementById("overlay");
    settingsMenu.style.display = "block";
    overlay.style.display = "block";
    setTimeout(function() {
      settingsMenu.style.opacity = "1";
      overlay.style.opacity = "1";
    }, 10);
  }

  function closeSettings() {
    var settingsMenu = document.getElementById("settings");
    var overlay = document.getElementById("overlay");
    settingsMenu.style.opacity = "0";
    overlay.style.opacity = "0";
    setTimeout(function() {
      settingsMenu.style.display = "none";
      overlay.style.display = "none";
    }, 300);
  }