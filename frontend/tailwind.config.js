/** @type {import('tailwindcss').Config} */
module.exports = {
    content: [
        "./index.html",
        "./src/**/*.{js,ts,jsx,tsx}",
    ],
    theme: {
        extend: {
            animation: {
                'scale-up': 'scale-up 0.5s cubic-bezier(0.39, 0.575, 0.565, 1)',
            },
        },
        keyframes: {
            'scale-up': {
                '0%': { transform: 'scale(0)' },
                '100%': { transform: 'scale(1)' },
            },
        },
    },
    plugins: [],
};