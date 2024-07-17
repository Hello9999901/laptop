import type { Site, Page, Links, Socials } from "@types"

// Global
export const SITE: Site = {
  TITLE: "anyon_e",
  DESCRIPTION: "A high-end, open source RK3588-based laptop. Attempt the impossible.",
  AUTHOR: "Byran Huang",
}

// Progress Page
export const PROGRESS: Page = {
  TITLE: "Progress",
  DESCRIPTION: "Current progress, timeline, and milestones.",
}

// Blog Page
export const BLOG: Page = {
  TITLE: "Blog",
  DESCRIPTION: "Writing on topics I am passionate about.",
}

// Posts Page
export const POSTS: Page = {
  TITLE: "Posts",
  DESCRIPTION: "Updates on the development of anyon_e.",
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
    TEXT: "Progress",
    HREF: "/progress",
  },
  {
    TEXT: "Posts",
    HREF: "/posts",
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
