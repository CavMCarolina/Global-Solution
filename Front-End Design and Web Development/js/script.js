// Fechar pop-up
const popup = document.querySelector(".popup-pai");

const Close = function(event) {
    const clickOfElement = event.target.classList[0]
    const classNameArray = ["close", "popup-pai"]
    const isClassList = classNameArray.includes(clickOfElement)

    if (isClassList) {
        popup.classList.add("d-none");
        popup.classList.remove("d-block");
    }
}

popup.addEventListener("click", Close);

// Formulário
const nome = document.querySelector('#nome');
const email = document.querySelector('#email');
const enviar = document.querySelector('#enviar');
const validar = document.createElement('v');

// Função para apagar os input quando forem enviados
function clearForm() {
    nome.value = ''
    email.value = ''
}

enviar.addEventListener("click", function(event) {
    event.preventDefault();

    if (nome.value.trim() === '') {
        validar.textContent = "Campo obrigatório.";
        nome.insertAdjacentElement ("afterend", validar);
        validar.setAttribute("class", "validar");
        return false;
    }

    if (email.value.trim() === '') {
        validar.textContent = "Campo obrigatório.";
        email.insertAdjacentElement ("afterend", validar);
        validar.setAttribute("class", "validar");
        return false;
    }

    console.log("Nome: ", nome.value);
    console.log("Email: ", email.value);
    validar.classList.add("d-none");
    clearForm();
})