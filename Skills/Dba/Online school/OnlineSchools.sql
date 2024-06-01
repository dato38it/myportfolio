--
-- PostgreSQL database dump
--

-- Dumped from database version 14.2 (Ubuntu 14.2-1.pgdg20.04+1)
-- Dumped by pg_dump version 14.2 (Ubuntu 14.2-1.pgdg20.04+1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: person; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.person (
    id integer,
    email character varying
);


ALTER TABLE public.person OWNER TO postgres;

--
-- Name: sales1; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.sales1 (
    product_id integer NOT NULL,
    order_id integer NOT NULL,
    quantity integer
);


ALTER TABLE public.sales1 OWNER TO postgres;

--
-- Name: superheroes; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.superheroes (
    id integer NOT NULL,
    name character varying(100),
    align character varying(30),
    eye character varying(30),
    hair character varying(30),
    gender character varying(30),
    appearances integer,
    year integer,
    universe character varying(10)
);


ALTER TABLE public.superheroes OWNER TO postgres;

--
-- Name: superheroes1; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.superheroes1 (
    id integer NOT NULL,
    name character varying(100),
    align character varying(30),
    eye character varying(30),
    hair character varying(30),
    gender character varying(30),
    appearances integer,
    year integer,
    universe character varying(10)
);


ALTER TABLE public.superheroes1 OWNER TO postgres;

--
-- Name: superheroes2; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.superheroes2 (
    id integer NOT NULL,
    name character varying(100) NOT NULL,
    align character varying(30),
    eye character varying(30),
    hair character varying(30),
    gender character varying(30),
    appearances integer,
    year integer,
    universe character varying(10)
);


ALTER TABLE public.superheroes2 OWNER TO postgres;

--
-- Name: superheroes3; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.superheroes3 (
    id integer NOT NULL,
    name character varying(100),
    align character varying(30),
    eye character varying(30),
    hair character varying(30),
    gender character varying(30),
    appearances integer,
    year integer,
    universe character varying(10)
);


ALTER TABLE public.superheroes3 OWNER TO postgres;

--
-- Name: superheroes4; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.superheroes4 (
    id integer NOT NULL,
    name character varying(100) NOT NULL,
    align character varying(30),
    eye character varying(30),
    hair character varying(30),
    gender character varying(30),
    appearances integer,
    year integer,
    universe character varying(10)
);


ALTER TABLE public.superheroes4 OWNER TO postgres;

--
-- Name: superheroes_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.superheroes_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.superheroes_id_seq OWNER TO postgres;

--
-- Name: superheroes_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.superheroes_id_seq OWNED BY public.superheroes.id;


--
-- Name: superheroes id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.superheroes ALTER COLUMN id SET DEFAULT nextval('public.superheroes_id_seq'::regclass);


--
-- Data for Name: person; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.person (id, email) FROM stdin;
1	john@example.com
2	bob@example.com
\.


--
-- Data for Name: sales1; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.sales1 (product_id, order_id, quantity) FROM stdin;
\.


--
-- Data for Name: superheroes; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.superheroes (id, name, align, eye, hair, gender, appearances, year, universe) FROM stdin;
2	Spider-Man (Peter Parker)	Good\nCharacters	Hazel Eyes	Brown Hair	Male Characters	4043	1962	marvel
3	Spider-Man (Peter Parker)	Good Characters	Hazel Eyes	Brown Hair	Male Characters	4043	1962	marvel
4	Captain America (Steven Rogers)	Good Characters	Blue Eyes	White Hair	Male Characters	3360	1941	marvel
5	Wolverine (James Logan Howlett)	Neutral Characters	Blue Eyes	Black Hair	Male Characters	3061	1974	marvel
6	Benjamin Grimm (Earth-616)	Good Characters	Blue Eyes	No Hair	Male Characters	2255	1961	marvel
7	Reed Richards (Earth-616)	Good Characters	Brown Eyes	Brown Hair	Male Characters	2072	1961	marvel
8	Hulk (Robert Bruce Banner)	Good Characters	Brown Eyes	Brown Hair	Male Characters	2017	1962	marvel
9	Scott Summers (Earth-616)	Neutral Characters	Brown Eyes	Brown Hair	Male Characters	1955	1963	marvel
10	Jonathan Storm (Earth-616)	Good Characters	Blue Eyes	Blond Hair	Male Characters	1934	1961	marvel
11	Susan Storm (Earth-616)	Good Characters	Blue Eyes	Blond Hair	Female Characters	1713	1961	marvel
12	Ororo Munroe (Earth-616)	Good Characters	Blue Eyes	White Hair	Female Characters	1512	1975	marvel
13	Clinton Barton (Earth-616)	Good Characters	Blue Eyes	Blond Hair	Male Characters	1394	1964	marvel
14	Matthew Murdock (Earth-616)	Good Characters	Blue Eyes	Red Hair	Male Characters	1338	1964	marvel
\.


--
-- Data for Name: superheroes1; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.superheroes1 (id, name, align, eye, hair, gender, appearances, year, universe) FROM stdin;
\.


--
-- Data for Name: superheroes2; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.superheroes2 (id, name, align, eye, hair, gender, appearances, year, universe) FROM stdin;
\.


--
-- Data for Name: superheroes3; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.superheroes3 (id, name, align, eye, hair, gender, appearances, year, universe) FROM stdin;
\.


--
-- Data for Name: superheroes4; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.superheroes4 (id, name, align, eye, hair, gender, appearances, year, universe) FROM stdin;
\.


--
-- Name: superheroes_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.superheroes_id_seq', 14, true);


--
-- Name: sales1 sales1_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.sales1
    ADD CONSTRAINT sales1_pkey PRIMARY KEY (product_id, order_id);


--
-- Name: superheroes1 superheroes1_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.superheroes1
    ADD CONSTRAINT superheroes1_pkey PRIMARY KEY (id);


--
-- Name: superheroes2 superheroes2_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.superheroes2
    ADD CONSTRAINT superheroes2_pkey PRIMARY KEY (id);


--
-- Name: superheroes3 superheroes3_name_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.superheroes3
    ADD CONSTRAINT superheroes3_name_key UNIQUE (name);


--
-- Name: superheroes3 superheroes3_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.superheroes3
    ADD CONSTRAINT superheroes3_pkey PRIMARY KEY (id);


--
-- Name: superheroes4 superheroes4_name_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.superheroes4
    ADD CONSTRAINT superheroes4_name_key UNIQUE (name);


--
-- Name: superheroes4 superheroes4_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.superheroes4
    ADD CONSTRAINT superheroes4_pkey PRIMARY KEY (id);


--
-- Name: superheroes superheroes_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.superheroes
    ADD CONSTRAINT superheroes_pkey PRIMARY KEY (id);


--
-- Name: superheroes_name_idx; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX superheroes_name_idx ON public.superheroes USING btree (name);


--
-- PostgreSQL database dump complete
--

