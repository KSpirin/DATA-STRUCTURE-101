const QS = window.__QS__;
let correct = 0, answered = 0;

document.querySelectorAll('.q').forEach((card, qi) => {
  const btn = card.querySelector('.check');
  btn.addEventListener('click', () => {
    const sel = card.querySelector('input:checked');
    if (!sel) return;
    const chosen = parseInt(sel.value);
    const answer = QS[qi].correct;
    const opts = card.querySelectorAll('.opt');
    const exp = card.querySelector('.exp');

    opts.forEach((o, i) => {
      if (i === answer) o.classList.add('ok');
      else if (i === chosen && chosen !== answer) o.classList.add('err');
      o.querySelector('input').disabled = true;
    });

    exp.classList.add('show');
    if (chosen === answer) {
      correct++;
      exp.classList.add('ok');
    } else {
      exp.classList.add('err');
    }
    answered++;
    btn.disabled = true;
    document.querySelector('.score-bar strong').textContent = correct + ' / ' + answered;
  });
});
