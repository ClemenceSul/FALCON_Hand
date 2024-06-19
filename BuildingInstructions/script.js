// Carousel functionality
let currentSlideIndex = 0;

function showSlide(index) {
    const slides = document.querySelectorAll('.carousel-slide');
    const dots = document.querySelectorAll('.carousel-dots .dot');
    const prevButton = document.querySelector('.carousel-button.prev');
    const nextButton = document.querySelector('.carousel-button.next');

    if (index >= slides.length) {
        currentSlideIndex = 0;
    } else if (index < 0) {
        currentSlideIndex = slides.length - 1;
    } else {
        currentSlideIndex = index;
    }

    slides.forEach((slide, i) => {
        slide.style.display = (i === currentSlideIndex) ? 'block' : 'none';
    });

    dots.forEach((dot, i) => {
        dot.classList.toggle('active', i === currentSlideIndex);
    });

    // Disable previous button if at the beginning of the carousel
    prevButton.disabled = (currentSlideIndex === 0);

    // Disable next button if at the end of the carousel
    nextButton.disabled = (currentSlideIndex === slides.length - 1);
}

function changeSlide(step) {
    showSlide(currentSlideIndex + step);
}

function currentSlide(index) {
    showSlide(index - 1);
}


document.addEventListener('DOMContentLoaded', () => {
    const toggleOption1 = document.getElementById('toggleOption1');
    const toggleOption2 = document.getElementById('toggleOption2');

    // Toggle button logic
    toggleOption1.addEventListener('click', () => {
        toggleOption1.classList.add('active');
        toggleOption2.classList.remove('active');
        localStorage.setItem("image_type", "digital");
        const divWithClasses = document.querySelector('button.tab-button.active');
        showTabContent(divWithClasses, slideIndex = currentSlideIndex);
    });

    toggleOption2.addEventListener('click', () => {
        toggleOption2.classList.add('active');
        toggleOption1.classList.remove('active');
        localStorage.setItem("image_type", "real");
        const divWithClasses = document.querySelector('button.tab-button.active');
        showTabContent(divWithClasses, slideIndex = currentSlideIndex);
    });

    // Initialize default active button
    const set_image_type = localStorage.getItem('image_type');
    if (set_image_type == "digital") {
        toggleOption1.classList.add('active');
    } else {
        toggleOption2.classList.add('active');
    }

    showSlide(currentSlideIndex);
});
