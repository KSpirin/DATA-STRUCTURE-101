const params = new URLSearchParams(window.location.search);
const part = params.get('part') || 'midterm';

// Determine topics and labels based on the part
const topics = DATA[part] || DATA['midterm'];
const partLabel = part === 'midterm' ? 'Part 1' : 'Part 2';
const perTopic = part === 'midterm' ? 5 : 6;

document.getElementById('partName').innerHTML = `${partLabel} <span class="badge" style="display: ${part === 'final' ? 'inline-block' : 'none'}; margin-left: 0.5rem;">Maintaining</span>`;

if (part === 'final') {
  alert("⚠️ WARNING: This quiz is a draft and currently under review. It may contain incorrect answers or unverified content.");
}

// Topic tag colors (HSL hues)
const HUES = { 
  'C++': 210, 
  'Arrays': 160, 
  'Stack': 30, 
  'Queue': 280, 
  'Linked List': 340, 
  'Hash Table': 50, 
  'Heap': 120, 
  'Binary Tree': 200, 
  'BST': 260, 
  'AVL': 90, 
  'Graph': 0 
};

function shuffle(arr) {
  const a = [...arr];
  for (let i = a.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [a[i], a[j]] = [a[j], a[i]];
  }
  return a;
}

let state = {
  correct: 0,
  answered: 0
};

function initShuffle() {
  state.correct = 0; 
  state.answered = 0;
  updateScore();
  
  // Pick `perTopic` questions from each topic (equal distribution, preserving topic order)
  let selected = [];
  const totalPool = topics.reduce((s, t) => s + t.questions.length, 0);
  
  topics.forEach(t => {
    const pick = Math.min(perTopic, t.questions.length);
    const shuffled = shuffle(t.questions);
    selected.push(...shuffled.slice(0, pick));
  });
  
  document.getElementById('questionCount').textContent = `${selected.length} / ${totalPool} total`;
  
  renderQuiz(selected);
  window.scrollTo({ top: 0, behavior: 'smooth' });
}

function updateScore() {
  document.getElementById('scoreCorrect').textContent = state.correct;
  document.getElementById('scoreTotal').textContent = state.answered;
}

function renderQuiz(questions) {
  const container = document.getElementById('quizContainer');
  container.innerHTML = '';

  questions.forEach((q, idx) => {
    const hue = HUES[q.topic] || 0;
    const tagStyle = `background: hsla(${hue}, 50%, 30%, 0.3); border: 1px solid hsla(${hue}, 50%, 50%, 0.4); color: hsl(${hue}, 60%, 75%);`;

    const card = document.createElement('div');
    card.className = 'card';

    let optionsHtml = '';
    const labels = ['A', 'B', 'C', 'D', 'E', 'F'];
    
    q.options.forEach((opt, optIdx) => {
      optionsHtml += `
        <label class="option-label" id="lbl-${idx}-${optIdx}">
          <input type="radio" name="sq${idx}" value="${optIdx}">
          <span style="font-weight: 600; margin-right: 0.5rem;">${labels[optIdx]}.</span>
          <div class="option-text">${opt}</div>
        </label>
      `;
    });

    card.innerHTML = `
      <div class="card-header">
        <span class="q-num">Q${idx + 1}</span>
        <span class="topic-tag" style="${tagStyle}">${q.topic}</span>
      </div>
      <div class="q-text">${q.q}</div>
      <div class="options">
        ${optionsHtml}
      </div>
      <button class="check-btn" id="btn-${idx}">Check</button>
      <div class="explanation" id="exp-${idx}">
        <strong>Explanation:</strong><br>
        ${q.explanation || 'No explanation provided.'}
      </div>
    `;

    container.appendChild(card);

    // Events
    const radios = card.querySelectorAll(`input[name="sq${idx}"]`);
    radios.forEach(r => {
      r.addEventListener('change', (e) => {
        card.querySelectorAll('.option-label').forEach(l => l.classList.remove('selected'));
        e.target.closest('.option-label').classList.add('selected');
      });
    });

    const btn = card.querySelector(`#btn-${idx}`);
    btn.addEventListener('click', () => {
      const selectedRadio = card.querySelector(`input[name="sq${idx}"]:checked`);
      if (!selectedRadio) return;

      const chosen = parseInt(selectedRadio.value);
      const isCorrect = (chosen === q.correct);

      btn.disabled = true;
      radios.forEach(r => r.disabled = true);

      const exp = card.querySelector(`#exp-${idx}`);
      exp.classList.add('show', isCorrect ? 'correct' : 'wrong');

      const allLabels = card.querySelectorAll('.option-label');
      allLabels.forEach((label, i) => {
        if (i === q.correct) {
          label.classList.add('ok');
        } else if (i === chosen && !isCorrect) {
          label.classList.add('err');
        }
      });

      state.answered++;
      if (isCorrect) state.correct++;
      updateScore();
    });
  });
}

// Start immediately
initShuffle();
