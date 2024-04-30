
const anteInput = document.getElementById('ante');
const cardsPerAnteInput = document.getElementById('cardsPerAnte');
const deckSelect = document.getElementById('deck');
const stakeSelect = document.getElementById('stake');
const versionSelect = document.getElementById('version');
const seedInput = document.getElementById('seed');
const analyzeButton = document.getElementById('analyzeButton');
const copyLinkButton = document.getElementById('copyButton');
const downloadButton = document.getElementById('downloadButton');
const outputBox = document.getElementById('outputBox');

function copyLink() {
  const baseUrl = window.location.origin + window.location.pathname;
  const params = new URLSearchParams();

  // Add non-default input values as URL parameters
  if (anteInput.value !== '8') params.append('ante', anteInput.value);
  if (cardsPerAnteInput.value !== '15,50,50,50,50,50,50,50') params.append('cardsPerAnte', cardsPerAnteInput.value);
  if (deckSelect.value !== 'Red Deck') params.append('deck', deckSelect.value);
  if (stakeSelect.value !== 'White Stake') params.append('stake', stakeSelect.value);
  if (versionSelect.value != '10105') params.append('version', versionSelect.value);
  if (seedInput.value !== '') params.append('seed', seedInput.value);

  const url = `${baseUrl}?${params.toString()}`;

  // Copy the URL to the clipboard
  navigator.clipboard.writeText(url)
    .then(() => {
      alert('Link copied to clipboard!');
    })
    .catch((err) => {
      console.error('Failed to copy link: ', err);
    });
}


function performAnalysis() {
  // Get input values
  const ante = parseInt(document.getElementById('ante').value, 10);
  const cardsPerAnte = document.getElementById('cardsPerAnte').value.split(',').map(Number);
  const deck = document.getElementById('deck').value;
  const stake = document.getElementById('stake').value;
  const version = parseInt(document.getElementById('version').value);
  const seed = document.getElementById('seed').value.toUpperCase().replace(/0/g, 'O');

  output = "";

  // It's analysis time!
  var inst = new Immolate.Instance(seed);
  inst.params = new Immolate.InstParams(deck, stake, false, version);
  inst.initLocks(1, false, false);
  inst.lock("Overstock Plus");
  inst.lock("Liquidation");
  inst.lock("Glow Up");
  inst.lock("Reroll Glut");
  inst.lock("Omen Globe");
  inst.lock("Observatory");
  inst.lock("Nacho Tong");
  inst.lock("Recyclomancy");
  inst.lock("Tarot Tycoon");
  inst.lock("Planet Tycoon");
  inst.lock("Money Tree");
  inst.lock("Antimatter");
  inst.lock("Illusion");
  inst.lock("Petroglyph");
  inst.lock("Retcon");
  inst.lock("Palette");
  inst.setStake(stake);
  inst.setDeck(deck);
  var ghostDeck = (deck == "Ghost Deck");
  for (let a = 1; a <= ante; a++) {
    inst.initUnlocks(a, false);
    output += "==ANTE " + a + "==\n"
    output += "Boss: " + inst.nextBoss(a) + "\n";
    var voucher = inst.nextVoucher(a);
    output += "Voucher: " + voucher + "\n";
    inst.lock(voucher);
    // Unlock next level voucher
    for (let i = 0; i < Immolate.VOUCHERS.size(); i+=2) {
        if (Immolate.VOUCHERS.get(i) == voucher) {
            inst.unlock(Immolate.VOUCHERS.get(i+1));
        };
    };
    output += "Tags: " + inst.nextTag(a) + ", " + inst.nextTag(a) + "\n";

    output += "Shop Queue: \n";
    for (let q = 1; q <= cardsPerAnte[a-1]; q++) {
      output += q + ") ";
      var item = inst.nextShopItem(a);
      if (item.type == "Joker") {
        if (item.jokerData.stickers.eternal) output += "Eternal ";
        if (item.jokerData.stickers.perishable) output += "Perishable ";
        if (item.jokerData.stickers.rental) output += "Rental ";
        if (item.jokerData.edition != "No Edition") output += item.jokerData.edition + " ";
      }
      output += item.item + "\n";
      item.delete();
    }

    output += "\nPacks: \n";
    var numPacks = (inst == 1) ? 4 : 6;
    for (let p = 1; p <= numPacks; p++) {
      var pack = inst.nextPack(a);
      output += pack + " - ";
      var packInfo = Immolate.packInfo(pack);
      if (packInfo.type == "Celestial Pack") {
        var cards = inst.nextCelestialPack(packInfo.size, a);
        for (let c = 0; c < packInfo.size; c++) {
          output += cards.get(c);
          output += (c + 1 != packInfo.size) ? ", " : "";
        }
        cards.delete();
      }
      if (packInfo.type == "Arcana Pack") {
        var cards = inst.nextArcanaPack(packInfo.size, a);
        for (let c = 0; c < packInfo.size; c++) {
          output += cards.get(c);
          output += (c + 1 != packInfo.size) ? ", " : "";
        }
        cards.delete();
      }
      if (packInfo.type == "Spectral Pack") {
        var cards = inst.nextSpectralPack(packInfo.size, a);
        for (let c = 0; c < packInfo.size; c++) {
          output += cards.get(c);
          output += (c + 1 != packInfo.size) ? ", " : "";
        }
        cards.delete();
      }
      if (packInfo.type == "Buffoon Pack") {
        var cards = inst.nextBuffoonPack(packInfo.size, a);
        for (let c = 0; c < packInfo.size; c++) {
          var joker = cards.get(c);
          if (joker.stickers.eternal) output += "Eternal ";
          if (joker.stickers.perishable) output += "Perishable ";
          if (joker.stickers.rental) output += "Rental ";
          if (joker.edition != "No Edition") output += joker.edition + " ";
          output += joker.joker;
          joker.delete();
          output += (c + 1 != packInfo.size) ? ", " : "";
        }
        cards.delete();
      }
      if (packInfo.type == "Standard Pack") {
        var cards = inst.nextStandardPack(packInfo.size, a);
        for (let c = 0; c < packInfo.size; c++) {
          var card = cards.get(c);
          if (card.seal != "No Seal") output += card.seal + " ";
          if (card.edition != "No Edition") output += card.edition + " ";
          if (card.enhancement != "No Enhancement") output += card.enhancement + " ";
          var rank = card.base[2];
          if (rank == "T") output += "10";
          else if (rank == "J") output += "Jack";
          else if (rank == "Q") output += "Queen";
          else if (rank == "K") output += "King";
          else if (rank == "A") output += "Ace";
          else output += rank;
          output += " of ";
          var suit = card.base[0];
          if (suit == "C") output += "Clubs";
          else if (suit == "S") output += "Spades";
          else if (suit == "D") output += "Diamonds";
          else if (suit == "H") output += "Hearts";
          card.delete();
          output += (c + 1 != packInfo.size) ? ", " : "";
        }
        cards.delete();
      }
      output += "\n";
    }

    output += "\n";
  };

  inst.delete();

  // Update output box with analysis result
  document.getElementById('outputBox').value = output;
}

function decrementRerollNumber() {
    document.getElementById("reroll-input").value--;
    if (document.getElementById("reroll-input").value<1) document.getElementById("reroll-input").value=1;
    setShop();
}

function incrementRerollNumber() {
    document.getElementById("reroll-input").value++;
    if (document.getElementById("reroll-input").value > 999) {
        document.getElementById("reroll-input").value = 999;
    }
    setShop();
}
function decrementAnteNumber() {
    document.getElementById("ante-input").value--;
    if (document.getElementById("ante-input").value<1) document.getElementById("ante-input").value=1;
    setShop();
}

function incrementAnteNumber() {
    document.getElementById("ante-input").value++;
    if (document.getElementById("ante-input").value > 39) {
        document.getElementById("ante-input").value = 39;
    }
    setShop();
}
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

// This will list every result from a seed.
var seedRegistry = {}
var inst;
function seekItem(ID, n) {
    if (!(ID in seedRegistry)) {
        seedRegistry[ID] = [];
    }
    while (seedRegistry[ID].length < n) {
        seedRegistry[ID].push(nextItem(ID));
    }
    return seedRegistry[ID][n-1];
 }
function nextItem(ID) {
    var tokenizedID = ID.split("-");
    if (tokenizedID[0] == "shop") {
        return inst.nextShopItem(parseInt(tokenizedID[1]));
    }
    if (tokenizedID[0] == "voucher") {
        return inst.nextVoucher(parseInt(tokenizedID[1]));
    }
    if (tokenizedID[0] == "pack") {
        return inst.nextPack(parseInt(tokenizedID[1]));
    }
}
function setShop() {
    var shopCards = document.querySelector(".main-cards");
    shopCards.innerHTML = '';
    for (let i = 0; i < 2; i++) {
        var newCard = document.createElement("div");
        newCard.className = "card";
        newCard.innerHTML = seekItem("shop-"+document.getElementById("ante-input").value, i+1+2*(document.getElementById("reroll-input").value-1)).item;
        shopCards.appendChild(newCard);
    }
    var packCards = document.querySelector(".pack-area");
    packCards.innerHTML = '';
    for (let i = 0; i < 2; i++) {
        var newCard = document.createElement("div");
        newCard.className = "card";
        newCard.innerHTML = seekItem("pack-"+document.getElementById("ante-input").value, i+1);
        packCards.appendChild(newCard);
    }
    var voucherCards = document.querySelector(".voucher-area");
    voucherCards.innerHTML = '';
    var newCard = document.createElement("div");
    newCard.className = "card";
    newCard.innerHTML = seekItem("voucher-"+document.getElementById("ante-input").value, 1);
    voucherCards.appendChild(newCard);
}
function resetRegistry() {
    seedRegistry = {}
    inst.delete();
    // Get input values
    const ante = parseInt(document.getElementById('ante').value, 10);
    const cardsPerAnte = document.getElementById('cardsPerAnte').value.split(',').map(Number);
    const deck = document.getElementById('deck').value;
    const stake = document.getElementById('stake').value;
    const version = parseInt(document.getElementById('version').value);
    const seed = document.getElementById('seed').value.toUpperCase().replace(/0/g, 'O');
    // It's analysis time!
    inst = new Immolate.Instance(seed);
    inst.params = new Immolate.InstParams(deck, stake, false, version);
    inst.params.resampling = false;
    inst.setStake(stake);
    inst.setDeck(deck);
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
        setShop()
    });
    document.getElementById("ante-input").addEventListener('input', () => {
        document.getElementById("ante-input").value = parseInt(document.getElementById("ante-input").value)
        if (document.getElementById("ante-input").value < 1) {
            document.getElementById("ante-input").value = 1;
        } else if (document.getElementById("ante-input").value > 39) {
            document.getElementById("ante-input").value = 39;
        }
        if (isNaN(document.getElementById("ante-input").value)) {
            document.getElementById("ante-input").value = 1;
        }
        setShop()
    });
    function filterSeed(seed) {
    const filteredSeed = seed.replace(/[^A-Za-z0-9]/g, '').toUpperCase().replace(/0/g, 'O');

    // Truncate the seed if it's longer than 8 characters
    return filteredSeed.slice(0, 8);
    }

    const seedInput = document.getElementById('seed');
      const cardsPerAnteInput = document.getElementById('cardsPerAnte');
      const anteInput = document.getElementById('ante');
      const deckInput = document.getElementById('deck');
      const stakeInput = document.getElementById('stake');
      const versionInput = document.getElementById('version');

      // Get seed value from URL parameters
      const urlParams = new URLSearchParams(window.location.search);
      const urlSeed = urlParams.get('seed');
      const urlAnte = urlParams.get('ante');
      const urlCardsPerAnte = urlParams.get('cardsPerAnte');
      const urlDeck = urlParams.get('deck');
      const urlStake = urlParams.get('stake');
      const urlVersion = urlParams.get('version');

      // Set default seed value
      if (urlAnte) {
        anteInput.value = urlAnte;
        anteInput.value = Math.min(anteInput.value, 39);
        anteInput.value = Math.max(anteInput.value, 1);
        cardsPerAnteInput.value = "15,50,50,50,50,50,50,50";
        var input = cardsPerAnteInput.value.split(',').map(Number);
        var fixedInput = []
        for (let i = 0; i < anteInput.value; i++) {
          if (input.length < i) {
            fixedInput.push(0);
          } else {
            fixedInput.push(input[i]);
          }
          if (fixedInput[i] == undefined) fixedInput[i] = 0;
          if (isNaN(fixedInput[i])) fixedInput[i] = 0;
        }
        cardsPerAnteInput.value = fixedInput;
      }
      if (urlCardsPerAnte) {
        cardsPerAnteInput.value = urlCardsPerAnte;
        var input = cardsPerAnteInput.value.split(',').map(Number);
        var fixedInput = []
        for (let i = 0; i < anteInput.value; i++) {
          if (input.length < i) {
            fixedInput.push(0);
          } else {
            fixedInput.push(input[i]);
          }
          if (fixedInput[i] == undefined) fixedInput[i] = 0;
          if (isNaN(fixedInput[i])) fixedInput[i] = 0;
        }
        cardsPerAnteInput.value = fixedInput;
      }
      if (urlDeck) {
        deckInput.value = urlDeck;
      }
      if (urlStake) {
        stakeInput.value = urlStake;
      }
      if (urlSeed) {
        seedInput.value = filterSeed(urlSeed);
      }
      if (urlVersion) {
        versionInput.value = urlVersion;
      }
    
    
    // Add event listener for the "Copy Link" button
    document.getElementById('copyButton').addEventListener('click', copyLink);
    document.getElementById('downloadButton').addEventListener('click', () => {
        const filename = seedInput.value + "_analysis.txt";
        const content = outputBox.value;
      
        const blob = new Blob([content], { type: 'text/plain' });
        const url = URL.createObjectURL(blob);
      
        const a = document.createElement('a');
        a.href = url;
        a.download = filename;
        a.click();
      
        URL.revokeObjectURL(url);
      });
      
// Add event listener to the "Analysis" button
document.getElementById('analyzeButton').addEventListener('click', performAnalysis);
// Add event listener for input event
seedInput.addEventListener('input', () => {
    seedInput.value = filterSeed(seedInput.value);
    resetRegistry()
    setShop()
  });
  
deckInput.addEventListener('input', () => {
    resetRegistry()
    setShop()
  });
  stakeInput.addEventListener('input', () => {
      resetRegistry()
      setShop()
    });
    
versionInput.addEventListener('input', () => {
    resetRegistry()
    setShop()
  });

  anteInput.addEventListener('input', () => {
    anteInput.value = Math.min(anteInput.value, 39);
    anteInput.value = Math.max(anteInput.value, 1);
    var input = cardsPerAnteInput.value.split(',').map(Number);
    var fixedInput = []
    for (let i = 0; i < anteInput.value; i++) {
      if (input.length < i) {
        fixedInput.push(0);
      } else {
        fixedInput.push(input[i]);
      }
      if (fixedInput[i] == undefined) fixedInput[i] = 0;
      if (isNaN(fixedInput[i])) fixedInput[i] = 0;
    }
    cardsPerAnteInput.value = fixedInput;
  });
  cardsPerAnteInput.addEventListener('input', () => {
    var input = cardsPerAnteInput.value.split(',').map(Number);
    var fixedInput = []
    for (let i = 0; i < anteInput.value; i++) {
      if (input.length < i) {
        fixedInput.push(0);
      } else {
        fixedInput.push(input[i]);
      }
      if (fixedInput[i] == undefined) fixedInput[i] = 0;
      if (isNaN(fixedInput[i])) fixedInput[i] = 0;
    }
    cardsPerAnteInput.value = fixedInput;
  });
    });