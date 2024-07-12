import type { Site, Page, Links, Socials } from "@types"

// Global
export const SITE: Site = {
  TITLE: "anyon_e",
  DESCRIPTION: "A high-end, open source RK3588-based laptop. Attempt the impossible.",
  AUTHOR: "Byran Huang",
}

// Work Page
export const WORK: Page = {
  TITLE: "Work",
  DESCRIPTION: "Places I have worked.",
}

// Blog Page
export const BLOG: Page = {
  TITLE: "Blog",
  DESCRIPTION: "Writing on topics I am passionate about.",
}

// Projects Page
export const PROJECTS: Page = {
  TITLE: "Projects",
  DESCRIPTION: "Recent projects I have worked on.",
}

// Search Page
export const SEARCH: Page = {
  TITLE: "Search",
  DESCRIPTION: "Search all posts and projects by keyword.",
}

// Links
export const LINKS: Links = [
  {
    TEXT: "Home",
    HREF: "/",
  },
  {
    TEXT: "Soon!",
    HREF: "/.",
  },
  {
    TEXT: "Loading...",
    HREF: "/.",
  },
]

// Socials
export const SOCIALS: Socials = [
  {
    NAME: "Email",
    ICON: "email",
    TEXT: "byran@mrx.ee",
    HREF: "mailto:byran@mrx.ee",
  },
  {
    NAME: "Github",
    ICON: "github",
    TEXT: "Hello9999901",
    HREF: "https://github.com/Hello9999901/laptop"
  },
  {
    NAME: "LinkedIn",
    ICON: "linkedin",
    TEXT: "Byran Huang",
    HREF: "https://www.linkedin.com/in/byran-huang/",
  },
  {
    NAME: "Main Website",
    ICON: "website",
    TEXT: "byran.tech",
    HREF: "https://byran.tech",
  },
]
