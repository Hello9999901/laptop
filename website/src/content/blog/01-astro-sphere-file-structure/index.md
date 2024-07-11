---
title: "Astro Sphere: File Structure"
summary: "You'll find these directories and files in the project. What do they do?"
date: "Mar 17 2024"
draft: false
tags:
- Tutorial
- Astro
- Astro Sphere
---

A one line summary of what each file and directory is for:
```js
/
├── public/ // Files publicly available to the browser
│   ├── fonts/ // The default fonts for Astro Sphere
│   │   └── atkinson-bold.woff  // default font weight 700
│   │   └── atkinson-regular.woff // default font weight 400
│   ├── js/ // Javascript that will be imported into <head>
│   │   └── animate.js // function for animating page elements
│   │   └── bg.js // function for generating the background
│   │   └── scroll.js // scroll handler for the header styles
│   │   └── theme.js // controls the light and dark theme
│   └── brand.svg //the icon that displays in header and footer
│   └── favicon.svg //the icon that displays in the browser
│   └── ui.svg // an svg sprite for all ui icons on the website
│   └── social.svg // an svg sprite for all social media icons
│   └── open-graph.jpg // the default image for open-graph
│   └── robots.txt // for web crawlers and bots to index the website
├── src/ // Everything that will be built for the website
│   ├── components/ // All astro and SolidJs components
│   ├── content/ // Contains all static markdown to be compiled
│   │   |  blog/ // Contains all blog post markdown
│   │   |  projects/ // Contains all projects markdown
│   │   |  work/ // Contains all work page markdown
│   │   |  legal/ // Contains all legal docs markdown
│   │   └── config.ts // Contains the collection config for Astro
│   ├── layouts/ // Reused layouts across the website
│   └── pages/ // All of the pages on the website
│   └── styles/ // CSS and global tailwind styles
│   └── lib/ // Global helper functions
│   └── consts.ts // Page metadata, general configuration
│   └── types.ts // Types for consts.ts
└── .gitignore // Files and directories to be ignored by Git
└── .eslintignore // Files and directories to be ignored by ESLint
└── eslintrc.cjs // ESLint configuration
└── astro.config.mjs // Astro configuration
└── tailwind.config.mjs // Tailwind configuration
└── tsconfig.json // Typescript configuration
└── package.json // All the installed packages
```